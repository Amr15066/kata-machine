"""LLM client module."""

from .base import LLMClient, TASK_QUERY, TASK_DOCUMENT
from .fake import FakeLLMClient
from . import prompts

__all__ = [
    "LLMClient",
    "GeminiClient",
    "DeepSeekClient",
    "FakeLLMClient",
    "TASK_QUERY",
    "TASK_DOCUMENT",
    "prompts",
]

# Provider clients pull in heavy optional SDKs. Importing them eagerly meant
# `import llm` failed on a machine without the Google SDK installed, which made
# the whole package untestable. Resolve them on first attribute access instead.
_LAZY = {
    "GeminiClient": (".gemini", "GeminiClient"),
    "DeepSeekClient": (".deepseek", "DeepSeekClient"),
}


def __getattr__(name: str):
    if name in _LAZY:
        from importlib import import_module

        module_name, attr = _LAZY[name]
        return getattr(import_module(module_name, __name__), attr)
    raise AttributeError(f"module {__name__!r} has no attribute {name!r}")


def __dir__():
    return sorted(__all__)
