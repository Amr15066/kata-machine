// Practice: depth-first search on an adjacency list.
// Teaches recursive graph traversal, path backtracking, and std::optional results.
#include <cassert>
#include <iostream>
#include <optional>
#include <vector>

using Graph = std::vector<std::vector<std::pair<int, int>>>;

bool walk(const Graph& graph,
          int current,
          int needle,
          std::vector<bool>& seen,
          std::vector<int>& path) {
    // TODO: implement
    // Hint: mark the current node seen, add it to path, recurse into unseen neighbors, and backtrack on failure.
    (void)graph;
    (void)current;
    (void)needle;
    (void)seen;
    (void)path;
    return false;
}

std::optional<std::vector<int>> dfs(const Graph& graph, int source, int needle) {
    // TODO: implement
    // Hint: validate the endpoints, initialize seen/path, then delegate to walk.
    (void)graph;
    (void)source;
    (void)needle;
    return std::nullopt;
}

int main() {
    const Graph graph{
        {{1, 7}, {2, 3}},
        {{4, 1}},
        {{3, 2}},
        {{6, 5}},
        {{5, 1}},
        {{6, 1}},
        {},
    };

    const std::vector<int> expected{0, 1, 4, 5, 6};
    assert(dfs(graph, 0, 6).value() == expected);
    assert(!dfs(graph, 6, 0).has_value());

    std::cout << "17_dfs_graph_list passed\n";
    return 0;
}
