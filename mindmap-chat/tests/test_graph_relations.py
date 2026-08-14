"""
Graph rendering tests.

``to_d3_graph()`` hardcoded relation="child" and confidence=0.8 for every edge,
so four of the five relation colours in the palette were unreachable and the
classifier's decision never influenced the visualisation.
"""

import pytest

from models import Block, ConversationGraph


def _graph_with_relation(relation, confidence=0.9):
    graph = ConversationGraph()
    root = Block(title="Root", intent="Root intent")
    graph.add_block(root)
    child = Block(
        parent_block_id=root.block_id,
        title="Child",
        intent="Child intent",
        relation=relation,
        relation_confidence=confidence,
    )
    graph.add_block(child)
    return graph


@pytest.mark.parametrize(
    "relation,expected_colour",
    [
        ("continue", "#4CAF50"),
        ("deepen", "#66BB6A"),
        ("child", "#2196F3"),
        ("sibling", "#FF9800"),
        ("tangent", "#F44336"),
    ],
)
def test_every_relation_colour_is_reachable(relation, expected_colour):
    d3 = _graph_with_relation(relation).to_d3_graph()
    link = d3["links"][0]
    assert link["relation"] == relation
    assert link["color"] == expected_colour


def test_stroke_width_varies_by_relation():
    widths = {
        rel: _graph_with_relation(rel).to_d3_graph()["links"][0]["strokeWidth"]
        for rel in ("continue", "deepen", "child", "sibling", "tangent")
    }
    assert len(set(widths.values())) == 5, widths


def test_classifier_action_is_translated_to_relation():
    """The classifier says 'new_child'; the renderer speaks 'child'."""
    d3 = _graph_with_relation("new_child").to_d3_graph()
    assert d3["links"][0]["relation"] == "child"
    assert d3["links"][0]["color"] == "#2196F3"


def test_real_confidence_is_used_not_hardcoded():
    d3 = _graph_with_relation("deepen", confidence=0.42).to_d3_graph()
    assert d3["links"][0]["confidence"] == pytest.approx(0.42)


def test_unknown_relation_falls_back_to_child():
    d3 = _graph_with_relation("nonsense").to_d3_graph()
    assert d3["links"][0]["relation"] == "child"


def test_confidence_is_clamped():
    d3 = _graph_with_relation("deepen", confidence=7.5).to_d3_graph()
    assert d3["links"][0]["confidence"] == 1.0


def test_relation_survives_persistence():
    graph = _graph_with_relation("tangent", 0.33)
    restored = ConversationGraph.from_dict(graph.to_dict())
    link = restored.to_d3_graph()["links"][0]
    assert link["relation"] == "tangent"
    assert link["confidence"] == pytest.approx(0.33)


def test_root_block_produces_no_link():
    graph = ConversationGraph()
    graph.add_block(Block(title="Root", intent="Root intent"))
    assert graph.to_d3_graph()["links"] == []
