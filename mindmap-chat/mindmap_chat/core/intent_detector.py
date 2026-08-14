"""
Intent shift detection.
Determines if new message continues, deepens, or diverges from current block.
"""

from __future__ import annotations

import json
import logging
from typing import List, Optional

from llm.base import LLMClient, TASK_QUERY
from llm import prompts
from models import Block, BlockClassification, ConversationMessage
from core.embeddings import compute_similarity, embed_text
from config import config

logger = logging.getLogger(__name__)

ACTION_MAP = {
    "CONTINUE": "continue",
    "DEEPEN": "deepen",
    "NEW_CHILD": "new_child",
    "TANGENT": "tangent",
}


def detect_intent_shift(
    llm_client: LLMClient,
    current_block: Block,
    new_user_msg: str,
    last_messages: List[ConversationMessage],
    message_embedding: Optional[List[float]] = None,
) -> BlockClassification:
    """
    Detect if the new message represents an intent shift.
    
    Uses embedding similarity first (fast), then LLM classification if ambiguous.
    
    Args:
        llm_client: LLM client for embeddings and classification
        current_block: The current block
        new_user_msg: The new user message
        last_messages: Recent messages (for context)
        message_embedding: Precomputed embedding of ``new_user_msg``. Passing it
            avoids embedding the same message twice in one turn.
        
    Returns:
        BlockClassification with action and reasoning
    """
    
    # Step 1: Embed the new message (reuse if the caller already did)
    if message_embedding is None:
        message_embedding = embed_text(llm_client, new_user_msg, task_type=TASK_QUERY)
    
    # Step 2: Compare similarity to current block intent
    intent_similarity = compute_similarity(message_embedding, current_block.embedding)
    
    # Step 3: Make decision based on thresholds
    thresholds = config.thresholds
    
    if intent_similarity >= thresholds.continue_threshold:
        # Very high similarity: same topic
        return BlockClassification(
            action="continue",
            confidence=intent_similarity,
            reasoning=f"Message aligns strongly with block intent (similarity: {intent_similarity:.2f})"
        )
    
    if intent_similarity >= thresholds.deepen_threshold:
        # Medium-high similarity: deeper dive
        return BlockClassification(
            action="deepen",
            confidence=intent_similarity,
            reasoning=f"Message deepens the current topic (similarity: {intent_similarity:.2f})"
        )

    # Below deepen_threshold the embedding alone cannot decide, so ask the LLM.
    # The band still matters: it sets what we fall back to when the LLM is
    # unavailable or returns garbage. Previously both branches were identical
    # and always fell back to "continue", which pinned genuinely unrelated
    # messages onto the current block.
    if intent_similarity < thresholds.tangent_threshold:
        fallback_action = "tangent"
        band = "likely tangent"
    else:
        fallback_action = "new_child"
        band = "ambiguous"

    logger.debug(
        "Similarity %.3f is %s; escalating to LLM (fallback=%s)",
        intent_similarity,
        band,
        fallback_action,
    )

    return _classify_with_llm(
        llm_client,
        current_block,
        new_user_msg,
        last_messages,
        fallback_action=fallback_action,
        similarity=intent_similarity,
    )


def _classify_with_llm(
    llm_client: LLMClient,
    current_block: Block,
    new_user_msg: str,
    last_messages: List[ConversationMessage],
    fallback_action: str = "continue",
    similarity: float = 0.0,
) -> BlockClassification:
    """
    Use LLM to classify intent shift when embedding similarity is ambiguous.
    """
    
    # Format last messages for context
    last_user = last_messages[-2].content if len(last_messages) >= 2 else "(first message)"
    last_assistant = last_messages[-1].content if last_messages else "(no response yet)"
    
    base_prompt = prompts.prompt_classify_intent_shift(
        current_block.title,
        current_block.intent,
        current_block.summary or "(block just started)",
        last_user,
        last_assistant,
        new_user_msg
    )

    retry_prompt = (
        base_prompt
        + "\n\nReminder: Return a single valid JSON object only. No extra text."
    )

    for attempt, prompt in enumerate((base_prompt, retry_prompt), start=1):
        try:
            return _build_classification(llm_client.call_json(prompt))
        except json.JSONDecodeError:
            if attempt == 1:
                logger.warning("Classifier returned invalid JSON; retrying once")
                continue
            logger.error("Classifier returned invalid JSON twice; using fallback")
        except Exception as e:
            logger.error("Error in LLM classification: %s", e)
            break

    return BlockClassification(
        action=fallback_action,
        confidence=similarity,
        reasoning=(
            f"Fallback classification (similarity: {similarity:.2f}); "
            "LLM classification unavailable"
        ),
    )


def _build_classification(response_json: dict) -> BlockClassification:
    """Map a raw classifier response onto a BlockClassification."""
    llm_action = str(response_json.get("classification", "")).upper()
    action = ACTION_MAP.get(llm_action, "continue")

    new_blocks = _parse_new_blocks(response_json)
    if not new_blocks:
        legacy_title = response_json.get("new_block_title")
        legacy_intent = response_json.get("new_block_intent")
        if legacy_title or legacy_intent:
            new_blocks = [{
                "title": legacy_title or "Untitled",
                "intent": legacy_intent or "New discussion",
            }]

    try:
        confidence = float(response_json.get("confidence", 0.5))
    except (TypeError, ValueError):
        confidence = 0.5
    confidence = min(max(confidence, 0.0), 1.0)

    return BlockClassification(
        action=action,
        confidence=confidence,
        reasoning=response_json.get("reasoning", ""),
        new_block_title=response_json.get("new_block_title"),
        new_block_intent=response_json.get("new_block_intent"),
        new_blocks=new_blocks,
    )


def _parse_new_blocks(response_json: dict) -> list[dict]:
    new_blocks = []
    for item in response_json.get("new_blocks", []) or []:
        if not isinstance(item, dict):
            continue
        title = item.get("title")
        intent = item.get("intent")
        if not title and not intent:
            continue
        new_blocks.append({
            "title": title or "Untitled",
            "intent": intent or "New discussion",
        })
    return new_blocks
