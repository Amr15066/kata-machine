"""
Block lifecycle management.
Creating, updating, and summarizing blocks.
"""

import logging
from typing import Optional
from llm.base import LLMClient, TASK_DOCUMENT
from llm import prompts
from models import Block, ConversationGraph, ConversationMessage
from core.embeddings import embed_text
from core.context_builder import construct_summary_prompt_context
from config import config

logger = logging.getLogger(__name__)


def create_root_block(llm_client: LLMClient, user_message: str) -> Block:
    """
    Create the root block from first user message.
    Extracts intent and generates title.
    
    Args:
        llm_client: LLM client
        user_message: The first user message
        
    Returns:
        New Block instance
    """
    # Extract intent from message
    prompt = prompts.prompt_extract_intent_from_message(user_message)

    try:
        response = llm_client.call_json(prompt)
    except Exception as e:
        # A malformed intent extraction should not lose the user's message.
        logger.warning("Intent extraction failed, using fallback: %s", e)
        response = {}

    intent = response.get("intent") or "Initial conversation"
    title = response.get("title") or _fallback_title(user_message)
    
    # Embed the intent
    intent_embedding = embed_text(llm_client, intent, task_type=TASK_DOCUMENT)
    
    # Create block
    block = Block(
        title=title,
        intent=intent,
        embedding=intent_embedding,
    )
    
    return block


def create_child_block(llm_client: LLMClient, parent_block: Block, 
                      title: str, intent: str,
                      relation: str = "child",
                      relation_confidence: float = 0.8) -> Block:
    """
    Create a child block.
    
    Args:
        llm_client: LLM client for embedding
        parent_block: Parent block
        title: Block title
        intent: Block intent
        relation: How this block relates to its parent (drives graph rendering)
        relation_confidence: Classifier confidence for that relation
        
    Returns:
        New Block instance
    """
    # Embed the intent
    intent_embedding = embed_text(llm_client, intent, task_type=TASK_DOCUMENT)
    
    # Create block
    block = Block(
        parent_block_id=parent_block.block_id,
        title=title,
        intent=intent,
        relation=relation,
        relation_confidence=relation_confidence,
        embedding=intent_embedding,
    )
    
    # Update parent
    parent_block.add_child(block.block_id)
    
    return block


def summarize_block(llm_client: LLMClient, graph: ConversationGraph, 
                   block: Block) -> None:
    """
    Auto-summarize a block using LLM.
    Updates block in-place with summary, key_points, open_questions.
    
    Args:
        llm_client: LLM client
        graph: Conversation graph
        block: Block to summarize
    """
    # Get context for summarization
    context = construct_summary_prompt_context(graph, block)
    
    # Call LLM
    prompt = prompts.prompt_generate_block_summary(block.intent, context)
    
    try:
        response = llm_client.call_json(prompt)
        
        # Update block
        block.summary = response.get("summary", "")
        block.key_points = response.get("key_points", [])
        block.open_questions = response.get("open_questions", [])
        
        # Update title if suggested
        new_title = response.get("title_suggestion")
        if new_title:
            block.title = new_title

        # Record what this summary covers so we know when it goes stale.
        block.summarized_at_message_count = len(block.conversation_refs)

        logger.info("Block '%s' summarized", block.title)
    
    except Exception as e:
        logger.error("Error summarizing block '%s': %s", block.title, e)


def maybe_auto_summarize(llm_client: LLMClient, graph: ConversationGraph, 
                        block: Block) -> None:
    """
    Summarize a block once it has enough messages, and re-summarize as it grows.

    The original guard was ``not block.summary``, so a block was summarized
    exactly once and then never again. Every message after that fell outside
    both the summary and the 3-message context window, and was silently
    invisible to the model from then on.
    
    Args:
        llm_client: LLM client
        graph: Conversation graph
        block: Block to check
    """
    message_count = len(block.conversation_refs)

    if not block.summary:
        if message_count >= config.auto_summarize_after_n_messages:
            logger.info("Auto-summarizing block (reached %d messages)", message_count)
            summarize_block(llm_client, graph, block)
        return

    messages_since_summary = message_count - block.summarized_at_message_count
    if messages_since_summary >= config.resummarize_every_n_messages:
        logger.info(
            "Re-summarizing block (%d new messages since last summary)",
            messages_since_summary,
        )
        summarize_block(llm_client, graph, block)


def _fallback_title(user_message: str, max_words: int = 6) -> str:
    """Derive a readable title when the model gives us nothing usable."""
    words = (user_message or "").strip().split()
    if not words:
        return "Untitled"
    title = " ".join(words[:max_words])
    return title if len(words) <= max_words else f"{title}..."
