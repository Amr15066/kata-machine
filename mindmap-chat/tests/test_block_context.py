"""
Block summarisation and context construction tests.

Two silent context-loss bugs are covered here:
  * a block was summarised exactly once, ever (``not block.summary`` guard);
  * a child block never saw its parent, so a DEEPEN lost its thread.
"""

import pytest

from config import config
from core.block_manager import maybe_auto_summarize, create_child_block
from core.context_builder import construct_block_context, collect_ancestors
from models import Block, ConversationGraph, ConversationMessage


def _add_messages(graph, block, count):
    for i in range(count):
        msg = ConversationMessage(
            block_id=block.block_id,
            role="user" if i % 2 == 0 else "assistant",
            content=f"message {i}",
        )
        graph.add_message(msg)
        block.add_message_ref(msg.message_id)


SUMMARY = {
    "summary": "a summary",
    "key_points": ["kp"],
    "open_questions": ["oq"],
}


def test_no_summary_below_threshold(fake_llm, graph):
    block = graph.blocks[graph.root_block_id]
    _add_messages(graph, block, config.auto_summarize_after_n_messages - 1)

    maybe_auto_summarize(fake_llm, graph, block)

    assert block.summary == ""
    assert fake_llm.call_count == 0


def test_summarizes_at_threshold(fake_llm, graph):
    block = graph.blocks[graph.root_block_id]
    _add_messages(graph, block, config.auto_summarize_after_n_messages)
    fake_llm.queue(SUMMARY)

    maybe_auto_summarize(fake_llm, graph, block)

    assert block.summary == "a summary"
    assert block.summarized_at_message_count == config.auto_summarize_after_n_messages


def test_resummarizes_as_block_grows(fake_llm, graph):
    """
    Regression: the old guard was ``not block.summary``, so this second call
    did nothing and every message after the first summary became invisible.
    """
    block = graph.blocks[graph.root_block_id]
    _add_messages(graph, block, config.auto_summarize_after_n_messages)
    fake_llm.queue(SUMMARY)
    maybe_auto_summarize(fake_llm, graph, block)
    first_calls = fake_llm.call_count

    _add_messages(graph, block, config.resummarize_every_n_messages)
    fake_llm.queue({**SUMMARY, "summary": "an updated summary"})
    maybe_auto_summarize(fake_llm, graph, block)

    assert fake_llm.call_count == first_calls + 1, "block never re-summarized"
    assert block.summary == "an updated summary"


def test_does_not_resummarize_before_growth_threshold(fake_llm, graph):
    block = graph.blocks[graph.root_block_id]
    _add_messages(graph, block, config.auto_summarize_after_n_messages)
    fake_llm.queue(SUMMARY)
    maybe_auto_summarize(fake_llm, graph, block)
    calls = fake_llm.call_count

    _add_messages(graph, block, 1)
    maybe_auto_summarize(fake_llm, graph, block)

    assert fake_llm.call_count == calls


def test_summary_failure_does_not_raise(fake_llm, graph):
    block = graph.blocks[graph.root_block_id]
    _add_messages(graph, block, config.auto_summarize_after_n_messages)
    fake_llm.queue("not json")

    maybe_auto_summarize(fake_llm, graph, block)  # must not raise

    assert block.summary == ""


def test_child_context_includes_parent(fake_llm, graph):
    """A freshly created child has no messages of its own."""
    parent = graph.blocks[graph.root_block_id]
    parent.summary = "We established the solver is implicit."

    child = create_child_block(
        fake_llm, parent, "Time stepping", "How the time step is chosen",
        relation="deepen", relation_confidence=0.8,
    )
    graph.add_block(child)

    context = construct_block_context(graph, child)

    assert "WHERE THIS CAME FROM" in context
    assert "We established the solver is implicit." in context


def test_ancestor_depth_is_bounded(fake_llm, graph):
    parent = graph.blocks[graph.root_block_id]
    current = parent
    for i in range(5):
        current = create_child_block(fake_llm, current, f"L{i}", f"intent {i}")
        graph.add_block(current)

    ancestors = collect_ancestors(graph, current, config.ancestor_context_depth)
    assert len(ancestors) == config.ancestor_context_depth


def test_ancestor_walk_survives_cycles(fake_llm, graph):
    a = graph.blocks[graph.root_block_id]
    b = create_child_block(fake_llm, a, "B", "b intent")
    graph.add_block(b)
    # Corrupt the parent chain into a cycle, as a bad persisted file could.
    a.parent_block_id = b.block_id

    ancestors = collect_ancestors(graph, b, max_depth=10)

    assert len(ancestors) <= 2  # terminates


def test_root_context_has_no_ancestor_section(graph):
    root = graph.blocks[graph.root_block_id]
    assert "WHERE THIS CAME FROM" not in construct_block_context(graph, root)
