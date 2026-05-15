// Practice: breadth-first search on an adjacency matrix.
// Teaches iterative graph traversal, parent reconstruction, and std::optional paths.
#include <algorithm>
#include <cassert>
#include <iostream>
#include <optional>
#include <vector>

std::optional<std::vector<int>> bfs(const std::vector<std::vector<int>>& graph, int source, int needle) {
    // TODO: implement
    // Hint: use a queue, track parents, then rebuild the path from needle back to source.
    (void)graph;
    (void)source;
    (void)needle;
    return std::nullopt;
}

int main() {
    const std::vector<std::vector<int>> graph{
        {0, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 0, 0},
        {0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0},
    };

    const std::vector<int> expected{0, 1, 4, 5, 6};
    assert(bfs(graph, 0, 6).value() == expected);
    assert(!bfs(graph, 6, 0).has_value());

    std::cout << "16_bfs_graph_matrix passed\n";
    return 0;
}
