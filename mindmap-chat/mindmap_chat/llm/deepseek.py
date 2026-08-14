"""
DeepSeek API client implementation.
Uses DeepSeek for generation (answering) but Gemini for embeddings (cheap).
"""

import logging
import requests
from typing import Any, Dict, List

from .base import LLMClient, TASK_DOCUMENT
from config import config

logger = logging.getLogger(__name__)


class DeepSeekClient(LLMClient):
    """DeepSeek API client for generation, Gemini for embeddings."""

    def __init__(self):
        """Initialize DeepSeek client."""
        self.api_key = config.deepseek.api_key
        if not self.api_key:
            raise ValueError("DEEPSEEK_API_KEY is not set")

        self.model_name = config.deepseek.model_name
        self.base_url = "https://api.deepseek.com/chat/completions"

        # Reuse the Gemini client purely for embeddings, rather than configuring
        # a second SDK by hand.
        from .gemini import GeminiClient

        self._embedder = GeminiClient()

    def call(self, prompt: str, json_mode: bool = False) -> str:
        """
        Call DeepSeek API for text generation.
        
        Args:
            prompt: The prompt to send
            json_mode: If True, request JSON response
            
        Returns:
            The model's response
        """
        headers = {
            "Authorization": f"Bearer {self.api_key}",
            "Content-Type": "application/json",
        }
        
        payload = {
            "model": self.model_name,
            "messages": [
                {"role": "user", "content": prompt}
            ],
            "temperature": config.deepseek.temperature,
            "max_tokens": config.deepseek.max_output_tokens,
            "response_format": {"type": "json_object"} if json_mode else None,
        }
        
        # Remove None values
        payload = {k: v for k, v in payload.items() if v is not None}
        
        try:
            response = requests.post(self.base_url, json=payload, headers=headers, timeout=30)
            response.raise_for_status()
            data = response.json()
        except requests.RequestException as e:
            raise RuntimeError(f"DeepSeek API error: {e}") from e

        choices = data.get("choices") or []
        if not choices:
            raise RuntimeError(f"DeepSeek returned no choices: {data}")
        return choices[0]["message"]["content"]

    def embed(self, text: str, task_type: str = TASK_DOCUMENT) -> List[float]:
        """
        Generate embedding using Gemini (cheap, token-efficient).
        
        Args:
            text: Text to embed
            task_type: Retrieval role of this text
            
        Returns:
            Embedding vector
        """
        return self._embedder.embed(text, task_type=task_type)
