"""
Intent detection tests.

Covers the threshold bands, the previously-dead tangent threshold, and the
removal of the duplicate embedding call.
"""

import pytest

from config import config
from core.embeddings import compute_similarity
from core.intent_detector import detect_intent_shift
from llm.base import TASK_QUERY
from llm.fake import FakeLLMClient, deterministic_embedding
from models import Block


def _block_with_embedding(text, llm):
    return Block(title=text, intent=text, embedding=llm.embed(text))


def test_identical_text_continues_without_calling_llm(fake_llm):
    block = _block_with_embedding("transient flow solver behaviour", fake_llm)
    result = detect_intent_shift(
        fake_llm, block, "transient flow solver behaviour", []
    )
    assert result.action == "continue"
    assert fake_llm.call_count == 0, "high similarity must not cost an LLM call"


def test_unrelated_message_escalates_to_llm(fake_llm):
    block = _block_with_embedding("transient flow solver behaviour", fake_llm)
    fake_llm.queue({"classification": "TANGENT", "confidence": 0.9, "reasoning": "different"})

    result = detect_intent_shift(fake_llm, block, "best recipe for sourdough bread", [])

    assert fake_llm.call_count == 1
    assert result.action == "tangent"


def test_precomputed_embedding_is_reused(fake_llm):
    """Passing the embedding in must not trigger a second embed call."""
    block = _block_with_embedding("solver behaviour", fake_llm)
    baseline = fake_llm.embed_count

    detect_intent_shift(
        fake_llm, block, "solver behaviour", [],
        message_embedding=deterministic_embedding("solver behaviour", fake_llm.dim),
    )

    assert fake_llm.embed_count == baseline, "message was embedded again"


def test_message_embedded_once_when_not_supplied(fake_llm):
    block = _block_with_embedding("solver behaviour", fake_llm)
    baseline = fake_llm.embed_count
    detect_intent_shift(fake_llm, block, "solver behaviour", [])
    assert fake_llm.embed_count == baseline + 1


def test_query_task_type_used_for_user_message(fake_llm):
    block = _block_with_embedding("solver behaviour", fake_llm)
    fake_llm.embed_task_types.clear()
    detect_intent_shift(fake_llm, block, "solver behaviour", [])
    assert fake_llm.embed_task_types == [TASK_QUERY]


def test_llm_failure_below_tangent_threshold_falls_back_to_tangent():
    """
    The two lowest bands used to have identical bodies and both fell back to
    "continue", pinning unrelated messages onto the current block.
    """
    llm = FakeLLMClient(responses=[lambda _: (_ for _ in ()).throw(RuntimeError("api down"))])
    block = Block(
        title="Solvers",
        intent="transient flow solver behaviour",
        embedding=deterministic_embedding("transient flow solver behaviour"),
    )

    result = detect_intent_shift(llm, block, "sourdough bread proving times", [])

    assert result.action == "tangent"


def test_llm_returning_garbage_is_retried_then_falls_back():
    llm = FakeLLMClient(responses=["not json at all", "still not json"])
    block = Block(
        title="Solvers",
        intent="transient flow solver behaviour",
        embedding=deterministic_embedding("transient flow solver behaviour"),
    )

    result = detect_intent_shift(llm, block, "sourdough bread proving times", [])

    assert llm.call_count == 2, "should retry exactly once"
    assert result.action == "tangent"


def test_confidence_is_clamped_from_llm():
    llm = FakeLLMClient(responses=[{"classification": "NEW_CHILD", "confidence": 99}])
    block = Block(
        title="Solvers",
        intent="transient flow solver behaviour",
        embedding=deterministic_embedding("transient flow solver behaviour"),
    )
    result = detect_intent_shift(llm, block, "sourdough bread proving", [])
    assert 0.0 <= result.confidence <= 1.0


def test_empty_block_embedding_does_not_crash(fake_llm):
    fake_llm.queue({"classification": "CONTINUE", "confidence": 0.5})
    block = Block(title="New", intent="New", embedding=[])
    result = detect_intent_shift(fake_llm, block, "anything", [])
    assert result.action in {"continue", "deepen", "new_child", "tangent"}


def test_mismatched_embedding_dimensions_score_zero():
    assert compute_similarity([1.0, 0.0], [1.0, 0.0, 0.0]) == 0.0


def test_thresholds_are_ordered():
    t = config.thresholds
    assert t.tangent_threshold <= t.deepen_threshold <= t.continue_threshold
