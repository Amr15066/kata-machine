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
    seen[static_cast<std::size_t>(current)] = true;
    path.push_back(current);

    if (current == needle) {
        return true;
    }

    for (const auto& edge : graph[static_cast<std::size_t>(current)]) {
        const int next = edge.first;
        if (seen[static_cast<std::size_t>(next)]) {
            continue;
        }
        if (walk(graph, next, needle, seen, path)) {
            return true;
        }
    }

    path.pop_back();
    return false;
}

std::optional<std::vector<int>> dfs(const Graph& graph, int source, int needle) {
    if (source < 0 || needle < 0 ||
        source >= static_cast<int>(graph.size()) || needle >= static_cast<int>(graph.size())) {
        return std::nullopt;
    }

    std::vector<bool> seen(graph.size(), false);
    std::vector<int> path;
    if (walk(graph, source, needle, seen, path)) {
        return path;
    }
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
