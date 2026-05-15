#include <algorithm>
#include <cassert>
#include <iostream>
#include <optional>
#include <vector>

std::optional<std::vector<int>> bfs(const std::vector<std::vector<int>>& graph, int source, int needle) {
    if (source < 0 || needle < 0 ||
        source >= static_cast<int>(graph.size()) || needle >= static_cast<int>(graph.size())) {
        return std::nullopt;
    }

    std::vector<bool> seen(graph.size(), false);
    std::vector<int> parent(graph.size(), -1);
    std::vector<int> queue(graph.size());
    std::size_t head = 0;
    std::size_t tail = 0;

    queue[tail++] = source;
    seen[static_cast<std::size_t>(source)] = true;

    while (head < tail) {
        const int current = queue[head++];
        if (current == needle) {
            break;
        }

        for (std::size_t next = 0; next < graph[static_cast<std::size_t>(current)].size(); ++next) {
            if (graph[static_cast<std::size_t>(current)][next] == 0 || seen[next]) {
                continue;
            }
            seen[next] = true;
            parent[next] = current;
            queue[tail++] = static_cast<int>(next);
        }
    }

    if (!seen[static_cast<std::size_t>(needle)]) {
        return std::nullopt;
    }

    std::vector<int> path;
    for (int current = needle; current != -1; current = parent[static_cast<std::size_t>(current)]) {
        path.push_back(current);
    }
    std::reverse(path.begin(), path.end());
    return path;
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
