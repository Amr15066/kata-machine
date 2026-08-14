"""
Embedding utilities for similarity matching.
Uses the configured LLM client for embeddings.
"""

import math
from typing import List, Sequence
from llm.base import LLMClient, TASK_DOCUMENT


def compute_similarity(embedding1: Sequence[float], embedding2: Sequence[float]) -> float:
    """
    Compute cosine similarity between two embeddings.
    
    Args:
        embedding1: First embedding vector
        embedding2: Second embedding vector
        
    Returns:
        Similarity score in [-1, 1]; 0.0 if either vector is empty,
        zero-length, or the two differ in dimensionality.
    """
    if not embedding1 or not embedding2:
        return 0.0

    # Comparing vectors of different dimensions silently produced a truncated,
    # meaningless score under zip(). That happens whenever the embedding model
    # changes, so fail loud-ish (return 0) instead of quietly misrouting.
    if len(embedding1) != len(embedding2):
        return 0.0

    dot_product = 0.0
    sum_sq1 = 0.0
    sum_sq2 = 0.0
    for a, b in zip(embedding1, embedding2):
        dot_product += a * b
        sum_sq1 += a * a
        sum_sq2 += b * b

    if sum_sq1 == 0.0 or sum_sq2 == 0.0:
        return 0.0

    return dot_product / math.sqrt(sum_sq1 * sum_sq2)


def embed_text(llm_client: LLMClient, text: str, task_type: str = TASK_DOCUMENT) -> List[float]:
    """
    Generate embedding for text.
    
    Args:
        llm_client: LLM client instance
        text: Text to embed
        task_type: Retrieval role (query vs document)
        
    Returns:
        Embedding vector
    """
    return llm_client.embed(text, task_type=task_type)
