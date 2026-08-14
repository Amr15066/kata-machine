"""
Context construction for LLM calls.
Builds focused context from block data instead of dumping entire history.
"""

from typing import List
from models import Block, ConversationMessage, ConversationGraph
from config import config


def format_key_points(key_points: List[str]) -> str:
    """Format key points as bullet list."""
    if not key_points:
        return "(No key points yet)"
    return "\n".join(f"- {kp}" for kp in key_points)


def format_open_questions(open_questions: List[str]) -> str:
    """Format open questions as bullet list."""
    if not open_questions:
        return "(No open questions)"
    return "\n".join(f"- {oq}" for oq in open_questions)


def format_conversation_turns(messages: List[ConversationMessage]) -> str:
    """Format messages as conversation turns."""
    if not messages:
        return "(No messages yet)"
    
    turns = []
    for msg in messages:
        role = "User" if msg.role == "user" else "Assistant"
        turns.append(f"{role}: {msg.content}")
    
    return "\n\n".join(turns)


def collect_ancestors(graph: ConversationGraph, block: Block, max_depth: int) -> List[Block]:
    """
    Walk up the parent chain, nearest ancestor first.

    Guards against cycles, which are possible because parent links are rebuilt
    from persisted data rather than validated on write.
    """
    ancestors: List[Block] = []
    seen = {block.block_id}
    current_id = block.parent_block_id

    while current_id and len(ancestors) < max_depth:
        if current_id in seen:
            break
        parent = graph.blocks.get(current_id)
        if not parent:
            break
        ancestors.append(parent)
        seen.add(current_id)
        current_id = parent.parent_block_id

    return ancestors


def format_ancestor_context(ancestors: List[Block]) -> str:
    """Format the parent chain so a child block keeps the thread it came from."""
    if not ancestors:
        return ""

    lines = []
    for depth, ancestor in enumerate(ancestors, start=1):
        label = "Parent" if depth == 1 else f"Ancestor (level {depth})"
        summary = ancestor.summary or ancestor.intent or "(no summary yet)"
        lines.append(f"{label} - {ancestor.title or 'Untitled'}: {summary}")

    return "\n".join(lines)


def construct_block_context(graph: ConversationGraph, block: Block, 
                          max_messages: int = None,
                          ancestor_depth: int = None) -> str:
    """
    Construct minimal context for answering in a block.
    
    Args:
        graph: The conversation graph
        block: The current block
        max_messages: Max recent messages to include (uses config default if None)
        ancestor_depth: How many ancestors to summarize (uses config default if None)
        
    Returns:
        Formatted context string
    """
    if max_messages is None:
        max_messages = config.context_window_size
    if ancestor_depth is None:
        ancestor_depth = config.ancestor_context_depth
    
    # Get messages for this block
    block_messages = graph.get_block_messages(block.block_id)
    
    # Take last N messages
    recent_messages = block_messages[-max_messages:] if block_messages else []
    
    # Format components
    key_points_str = format_key_points(block.key_points)
    open_questions_str = format_open_questions(block.open_questions)
    recent_messages_str = format_conversation_turns(recent_messages)

    # A block created by DEEPEN/NEW_CHILD starts with zero messages. Without the
    # parent chain the model answers with no idea what is being deepened.
    ancestors = collect_ancestors(graph, block, ancestor_depth)
    ancestor_str = format_ancestor_context(ancestors)
    ancestor_section = f"""
WHERE THIS CAME FROM:
{ancestor_str}
""" if ancestor_str else ""

    context = f"""
BLOCK CONTEXT:
Title: {block.title}
Intent: {block.intent}
Summary: {block.summary}
{ancestor_section}
KEY POINTS COVERED:
{key_points_str}

OPEN QUESTIONS FROM THIS DISCUSSION:
{open_questions_str}

CONVERSATION HISTORY (last {len(recent_messages)} messages):
{recent_messages_str}
"""
    
    return context


def construct_summary_prompt_context(graph: ConversationGraph, block: Block) -> str:
    """
    Construct context for summarizing a block.
    Includes all messages for that block.
    
    Args:
        graph: The conversation graph
        block: The block to summarize
        
    Returns:
        Formatted context string
    """
    block_messages = graph.get_block_messages(block.block_id)
    messages_str = format_conversation_turns(block_messages)
    
    return f"""BLOCK INTENT: {block.intent}

MESSAGES IN THIS BLOCK:
{messages_str}"""
