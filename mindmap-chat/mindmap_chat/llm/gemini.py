"""
Gemini API client implementation.

Supports both Google SDKs:

  * ``google-generativeai`` (legacy) - module-level ``configure()`` + ``GenerativeModel``
  * ``google-genai`` (current)       - ``Client`` object, no ``configure()``

The original code fell back from the legacy SDK to the new one on ImportError
and then called ``genai.configure()`` regardless. That method does not exist on
the new SDK, so the fallback path could never work.
"""

from __future__ import annotations

import logging
from typing import List

from .base import LLMClient, TASK_DOCUMENT
from config import config

logger = logging.getLogger(__name__)

_LEGACY = "legacy"
_NEW = "new"


def _load_sdk():
    """Return (module, flavour). Prefers the current SDK."""
    try:
        from google import genai as new_genai  # type: ignore

        return new_genai, _NEW
    except ImportError:
        pass

    try:
        import google.generativeai as legacy_genai  # type: ignore

        return legacy_genai, _LEGACY
    except ImportError as exc:  # pragma: no cover - depends on environment
        raise ImportError(
            "No Google Gemini SDK found. Install one of:\n"
            "  pip install google-genai          (recommended)\n"
            "  pip install google-generativeai   (legacy)"
        ) from exc


class GeminiClient(LLMClient):
    """Gemini API client."""

    def __init__(self):
        if not config.gemini.api_key:
            raise ValueError("GEMINI_API_KEY is not set")

        self._sdk, self._flavour = _load_sdk()
        self.embedding_model = config.embeddings.model

        if self._flavour == _NEW:
            self._client = self._sdk.Client(api_key=config.gemini.api_key)
            self._model = None
        else:
            self._sdk.configure(api_key=config.gemini.api_key)
            self._client = None
            self._model = self._sdk.GenerativeModel(config.gemini.model_name)

        logger.debug("Gemini client initialised using %s SDK", self._flavour)

    def call(self, prompt: str, json_mode: bool = False) -> str:
        full_prompt = prompt
        if json_mode:
            full_prompt += "\n\nRESPOND ONLY WITH VALID JSON (no markdown, no extra text)."

        if self._flavour == _NEW:
            response = self._client.models.generate_content(
                model=config.gemini.model_name,
                contents=full_prompt,
                config={
                    "temperature": config.gemini.temperature,
                    "max_output_tokens": config.gemini.max_output_tokens,
                    **({"response_mime_type": "application/json"} if json_mode else {}),
                },
            )
        else:
            response = self._model.generate_content(
                full_prompt,
                generation_config={
                    "temperature": config.gemini.temperature,
                    "max_output_tokens": config.gemini.max_output_tokens,
                    **({"response_mime_type": "application/json"} if json_mode else {}),
                },
            )

        return _extract_text(response)

    def embed(self, text: str, task_type: str = TASK_DOCUMENT) -> List[float]:
        if self._flavour == _NEW:
            result = self._client.models.embed_content(
                model=self.embedding_model,
                contents=text,
                config={"task_type": task_type},
            )
            return list(result.embeddings[0].values)

        result = self._sdk.embed_content(
            model=self.embedding_model,
            content=text,
            task_type=task_type,
        )
        return list(result["embedding"])


def _extract_text(response) -> str:
    """
    Pull text out of a Gemini response without assuming it exists.

    ``response.text`` raises when the model returns no candidates - which
    happens on safety blocks, recitation stops and token exhaustion. Unguarded,
    that surfaced as an opaque 500 with no indication of the real cause.
    """
    text = getattr(response, "text", None)
    if text:
        return text

    feedback = getattr(response, "prompt_feedback", None)
    block_reason = getattr(feedback, "block_reason", None)
    if block_reason:
        raise RuntimeError(f"Gemini blocked the prompt: {block_reason}")

    candidates = getattr(response, "candidates", None) or []
    if not candidates:
        raise RuntimeError("Gemini returned no candidates and no text")

    finish_reason = getattr(candidates[0], "finish_reason", None)

    # Some SDK versions leave .text empty but still populate the parts.
    content = getattr(candidates[0], "content", None)
    parts = getattr(content, "parts", None) or []
    joined = "".join(getattr(p, "text", "") or "" for p in parts)
    if joined:
        return joined

    raise RuntimeError(f"Gemini returned an empty response (finish_reason={finish_reason})")
