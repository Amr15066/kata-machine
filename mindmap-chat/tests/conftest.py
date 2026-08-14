"""
Shared pytest fixtures.

The package uses top-level absolute imports (``from models import ...``), so
``mindmap_chat/`` itself has to be importable as a source root.
"""

import sys
from pathlib import Path

import pytest

PACKAGE_ROOT = Path(__file__).resolve().parent.parent / "mindmap_chat"
if str(PACKAGE_ROOT) not in sys.path:
    sys.path.insert(0, str(PACKAGE_ROOT))

from llm.fake import FakeLLMClient  # noqa: E402
from models import Block, ConversationGraph  # noqa: E402
from storage import JSONStorage  # noqa: E402


@pytest.fixture
def fake_llm():
    return FakeLLMClient()


@pytest.fixture
def storage(tmp_path):
    return JSONStorage(str(tmp_path / "data" / "conversation.json"))


@pytest.fixture
def graph(fake_llm):
    """A graph containing a single root block."""
    g = ConversationGraph()
    root = Block(
        title="Solvers",
        intent="Understand transient flow solvers",
        embedding=fake_llm.embed("Understand transient flow solvers"),
    )
    g.add_block(root)
    g.current_block_id = root.block_id
    return g
