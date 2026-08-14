"""
Configuration and environment settings.
Centralized place for API keys, model names, thresholds.
"""

import os
import logging
from dataclasses import dataclass, field
from pathlib import Path

from dotenv import load_dotenv

logger = logging.getLogger(__name__)

# Load .env from mindmap_chat folder
env_path = Path(__file__).parent / ".env"
load_dotenv(dotenv_path=env_path)


@dataclass
class GeminiConfig:
    """Gemini API configuration."""
    api_key: str = os.getenv("GEMINI_API_KEY", "")
    model_name: str = "gemini-3-flash-preview"  # Fast and generous free tier
    temperature: float = 0.7
    max_output_tokens: int = 1024


@dataclass
class EmbeddingConfig:
    """Embedding model configuration."""
    model: str = "gemini-embedding-001"
    # gemini-embedding-001 returns 3072 dimensions by default. The old value of
    # 384 was copied from a sentence-transformers model that is not used here.
    embedding_dim: int = 3072


@dataclass
class DetectionThresholds:
    """
    Cosine-similarity thresholds for intent detection.

    Bands, from most to least similar:
        sim >= continue_threshold                    -> continue (no LLM call)
        sim >= deepen_threshold                      -> deepen   (no LLM call)
        deepen > sim >= tangent_threshold            -> ambiguous, ask the LLM
        sim <  tangent_threshold                     -> likely tangent, ask the LLM

    These are unvalidated magic numbers inherited from the hackathon build.
    Treat them as a starting point and tune them against a labelled set
    (see tests/eval) before trusting them.
    """
    continue_threshold: float = 0.90  # Same topic
    deepen_threshold: float = 0.70  # Deeper dive
    sibling_threshold: float = 0.75  # Min similarity to reuse a block in another graph
    related_match_threshold: float = 0.60  # Looser match when surfacing related blocks
    tangent_threshold: float = 0.65  # Below this, treat as a probable topic change

    def __post_init__(self):
        if not self.deepen_threshold <= self.continue_threshold:
            raise ValueError(
                "deepen_threshold must be <= continue_threshold "
                f"(got {self.deepen_threshold} > {self.continue_threshold})"
            )
        if not self.tangent_threshold <= self.deepen_threshold:
            raise ValueError(
                "tangent_threshold must be <= deepen_threshold "
                f"(got {self.tangent_threshold} > {self.deepen_threshold})"
            )


@dataclass
class DeepSeekConfig:
    """DeepSeek API configuration (optional alternative generator)."""
    api_key: str = os.getenv("DEEPSEEK_API_KEY", "")
    model_name: str = "deepseek-chat"
    temperature: float = 0.7
    max_output_tokens: int = 1024


@dataclass
class AppConfig:
    """Application-wide configuration."""
    gemini: GeminiConfig = field(default_factory=GeminiConfig)
    deepseek: DeepSeekConfig = field(default_factory=DeepSeekConfig)
    embeddings: EmbeddingConfig = field(default_factory=EmbeddingConfig)
    thresholds: DetectionThresholds = field(default_factory=DetectionThresholds)
    auto_summarize_after_n_messages: int = 6
    # Re-summarize once a block has grown by this many messages since its last
    # summary. Without this a block is summarized exactly once, ever.
    resummarize_every_n_messages: int = 6
    storage_path: str = "./data/conversation.json"
    context_window_size: int = 3  # Last N messages to include in context
    # How many ancestor summaries to prepend so a deepened block keeps its thread.
    ancestor_context_depth: int = 2


# Global config instance
config = AppConfig()


def validate_config():
    """Validate that all required config is set."""
    if not config.gemini.api_key:
        raise ValueError("GEMINI_API_KEY environment variable not set")
    logger.info("Configuration validated")
