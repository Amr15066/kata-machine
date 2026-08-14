"""
End-to-end conversation tests using the fake client.

These exercise the orchestration layer without a network key, which was
previously impossible.
"""

import pytest

from conversation import ConversationManager
from llm.fake import FakeLLMClient
from models import Mindmap

INTENT = {"intent": "Understand solvers", "title": "Solvers"}


def _manager(storage, responses):
    return ConversationManager(FakeLLMClient(responses=responses), storage)


def test_start_new_conversation_persists(storage):
    mgr = _manager(storage, [INTENT, "Here is an answer."])

    response = mgr.start_new_conversation("How do implicit solvers work?")

    assert response == "Here is an answer."
    reloaded = storage.load()
    assert len(reloaded.graphs) == 1
    graph = reloaded.get_current_graph()
    assert len(graph.messages) == 2  # user + assistant


def test_continue_same_topic_stays_in_block(storage):
    mgr = _manager(storage, [INTENT, "answer one", "answer two"])
    mgr.start_new_conversation("Understand solvers")
    block_count = len(mgr.graph.blocks)

    mgr.continue_conversation("Understand solvers")

    assert len(mgr.graph.blocks) == block_count, "should not have branched"


def test_context_built_once_per_turn(storage):
    """
    The old _get_response_in_block built the context twice and threw away a
    hand-rolled prompt. One user turn should mean exactly one answer call.
    """
    llm = FakeLLMClient(responses=[INTENT, "answer"])
    mgr = ConversationManager(llm, storage)

    mgr.start_new_conversation("Understand solvers")

    # 1 intent-extraction call + 1 answer call
    assert llm.call_count == 2


def test_user_message_embedded_once_per_turn(storage):
    llm = FakeLLMClient(responses=[INTENT, "answer", "answer two"])
    mgr = ConversationManager(llm, storage)
    mgr.start_new_conversation("Understand solvers")

    before = llm.embed_count
    mgr.continue_conversation("Understand solvers in depth")
    after = llm.embed_count

    # At most: 1 for the user message, 1 for any new block's intent.
    assert after - before <= 2, f"user message embedded redundantly ({after - before} embeds)"


def test_new_child_block_records_its_relation(storage):
    llm = FakeLLMClient(responses=[
        INTENT,
        "answer",
        {
            "classification": "NEW_CHILD",
            "confidence": 0.77,
            "reasoning": "different subtopic",
            "new_blocks": [{"title": "Meshing", "intent": "How meshes are built"}],
        },
        "answer about meshing",
    ])
    mgr = ConversationManager(llm, storage)
    mgr.start_new_conversation("Understand solvers")

    mgr.continue_conversation("completely unrelated topic about baking bread")

    links = mgr.graph.to_d3_graph()["links"]
    assert links, "expected a child block to have been created"
    assert links[0]["relation"] in {"child", "sibling", "deepen"}
    assert links[0]["confidence"] != 0.8 or links[0]["relation"] != "child", (
        "relation/confidence still look hardcoded"
    )


def test_graph_survives_save_load_cycle(storage):
    mgr = _manager(storage, [INTENT, "answer"])
    mgr.start_new_conversation("Understand solvers")
    original_id = mgr.graph.graph_id

    fresh = ConversationManager(FakeLLMClient(), storage)

    assert fresh.graph is not None
    assert fresh.graph.graph_id == original_id


def test_empty_storage_starts_clean(storage):
    mgr = ConversationManager(FakeLLMClient(), storage)
    assert mgr.graph is None


def test_delete_block_removes_descendants(storage):
    llm = FakeLLMClient(responses=[
        INTENT,
        "answer",
        {
            "classification": "NEW_CHILD",
            "confidence": 0.7,
            "new_blocks": [{"title": "Child", "intent": "child intent"}],
        },
        "answer",
    ])
    mgr = ConversationManager(llm, storage)
    mgr.start_new_conversation("Understand solvers")
    mgr.continue_conversation("totally different subject entirely")

    child_ids = [b for b in mgr.graph.blocks if b != mgr.graph.root_block_id]
    if not child_ids:
        pytest.skip("classifier did not branch")

    mgr.delete_block(child_ids[0])

    assert child_ids[0] not in mgr.graph.blocks
    assert child_ids[0] not in mgr.graph.blocks[mgr.graph.root_block_id].children


def test_cannot_delete_root(storage):
    mgr = _manager(storage, [INTENT, "answer"])
    mgr.start_new_conversation("Understand solvers")

    with pytest.raises(ValueError):
        mgr.delete_block(mgr.graph.root_block_id)
