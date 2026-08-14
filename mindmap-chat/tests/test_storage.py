"""
Storage regression tests.

The original ``load()`` raised UnboundLocalError on any file without a
top-level "graphs" key, and its legacy-format migration sat after a return
statement, so it was unreachable.
"""

import json

import pytest

from models import Block, ConversationGraph, Mindmap


def test_load_missing_file_returns_empty(storage):
    mindmap = storage.load()
    assert isinstance(mindmap, Mindmap)
    assert mindmap.graphs == {}


def test_round_trip(storage):
    graph = ConversationGraph()
    root = Block(title="Root", intent="Root intent")
    graph.add_block(root)
    child = Block(parent_block_id=root.block_id, title="Child", intent="Child intent")
    graph.add_block(child)

    mindmap = Mindmap()
    mindmap.add_graph(graph)
    storage.save(mindmap)

    loaded = storage.load()
    assert len(loaded.graphs) == 1
    loaded_graph = loaded.get_current_graph()
    assert loaded_graph.root_block_id == root.block_id
    # rebuild_children must have restored the parent -> child link
    assert child.block_id in loaded_graph.blocks[root.block_id].children


def test_load_legacy_single_graph_format(storage):
    """A pre-Mindmap file has no 'graphs' key. This used to crash."""
    legacy = ConversationGraph()
    root = Block(title="Legacy root", intent="Legacy intent")
    legacy.add_block(root)

    storage.file_path.parent.mkdir(parents=True, exist_ok=True)
    storage.file_path.write_text(json.dumps(legacy.to_dict()), encoding="utf-8")

    loaded = storage.load()

    assert len(loaded.graphs) == 1
    graph = loaded.get_current_graph()
    assert graph.blocks[graph.root_block_id].title == "Legacy root"


def test_load_corrupted_json_returns_empty(storage):
    storage.file_path.parent.mkdir(parents=True, exist_ok=True)
    storage.file_path.write_text("{not json", encoding="utf-8")
    assert storage.load().graphs == {}


def test_load_non_dict_root_returns_empty(storage):
    storage.file_path.parent.mkdir(parents=True, exist_ok=True)
    storage.file_path.write_text("[1, 2, 3]", encoding="utf-8")
    assert storage.load().graphs == {}


def test_unknown_fields_are_ignored(storage):
    """Persisted data outlives the schema; unknown keys must not break loading."""
    graph = ConversationGraph()
    root = Block(title="Root", intent="Root intent")
    graph.add_block(root)
    mindmap = Mindmap()
    mindmap.add_graph(graph)
    storage.save(mindmap)

    raw = json.loads(storage.file_path.read_text(encoding="utf-8"))
    gid = next(iter(raw["graphs"]))
    bid = next(iter(raw["graphs"][gid]["blocks"]))
    raw["graphs"][gid]["blocks"][bid]["field_from_the_future"] = "boom"
    storage.file_path.write_text(json.dumps(raw), encoding="utf-8")

    loaded = storage.load()
    assert loaded.get_current_graph().blocks[bid].title == "Root"


def test_transaction_is_atomic_read_modify_write(storage):
    with storage.transaction() as mindmap:
        graph = ConversationGraph()
        graph.add_block(Block(title="In transaction", intent="x"))
        mindmap.add_graph(graph)

    reloaded = storage.load()
    assert len(reloaded.graphs) == 1


def test_save_leaves_no_temp_files(storage):
    mindmap = Mindmap()
    storage.save(mindmap)
    leftovers = list(storage.file_path.parent.glob(".tmp_*"))
    assert leftovers == []
