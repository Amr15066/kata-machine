"""
Deterministic in-memory LLM client for tests and offline development.

The real pipeline needs a network key for every single operation, which made
the whole system untestable and made threshold tuning guesswork. This client
implements the same interface with:

  * deterministic bag-of-words embeddings, so similar text really is more
    cosine-similar (no randomness, no network);
  * scriptable JSON/text responses;
  * call counters, so tests can assert that we stopped doing redundant work
    (e.g. embedding the same message twice per turn).
"""

from __future__ import annotations

import hashlib
import json
import math
import re
from typing import Any, Callable, Dict, List, Optional, Sequence, Union

from .base import LLMClient, TASK_DOCUMENT

_TOKEN_RE = re.compile(r"[a-z0-9]+")

Scripted = Union[str, Dict[str, Any], Callable[[str], Union[str, Dict[str, Any]]]]


def _tokenize(text: str) -> List[str]:
    return _TOKEN_RE.findall((text or "").lower())


class FakeLLMClient(LLMClient):
    """A deterministic, offline stand-in for a real LLM provider."""

    def __init__(
        self,
        responses: Optional[Sequence[Scripted]] = None,
        default_response: Scripted = "(fake response)",
        dim: int = 64,
    ):
        """
        Args:
            responses: Queue of scripted replies, consumed in order. Each item
                may be a string, a dict (serialized to JSON), or a callable
                taking the prompt and returning either.
            default_response: Used once the scripted queue is exhausted.
            dim: Embedding dimensionality.
        """
        self._responses: List[Scripted] = list(responses or [])
        self._default = default_response
        self.dim = dim

        # Observability for tests.
        self.call_count = 0
        self.embed_count = 0
        self.prompts: List[str] = []
        self.embedded_texts: List[str] = []
        self.embed_task_types: List[str] = []

    def queue(self, *responses: Scripted) -> "FakeLLMClient":
        """Append scripted responses. Returns self for chaining."""
        self._responses.extend(responses)
        return self

    def call(self, prompt: str, json_mode: bool = False) -> str:
        self.call_count += 1
        self.prompts.append(prompt)

        item = self._responses.pop(0) if self._responses else self._default
        if callable(item):
            item = item(prompt)
        if isinstance(item, (dict, list)):
            return json.dumps(item)
        return str(item)

    def embed(self, text: str, task_type: str = TASK_DOCUMENT) -> List[float]:
        self.embed_count += 1
        self.embedded_texts.append(text)
        self.embed_task_types.append(task_type)
        return deterministic_embedding(text, self.dim)


def deterministic_embedding(text: str, dim: int = 64) -> List[float]:
    """
    Hash tokens into a fixed-width L2-normalized vector.

    Texts sharing vocabulary land close together under cosine similarity, which
    is enough to exercise the threshold logic without calling an API.
    """
    vec = [0.0] * dim
    tokens = _tokenize(text)
    if not tokens:
        return vec

    for token in tokens:
        digest = hashlib.blake2b(token.encode("utf-8"), digest_size=8).digest()
        bucket = int.from_bytes(digest[:4], "big") % dim
        sign = 1.0 if digest[4] % 2 == 0 else -1.0
        vec[bucket] += sign

    norm = math.sqrt(sum(v * v for v in vec))
    if norm == 0:
        return vec
    return [v / norm for v in vec]
