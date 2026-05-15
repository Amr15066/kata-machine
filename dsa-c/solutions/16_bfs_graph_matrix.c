// BFS on Adjacency Matrix: find shortest path in unweighted graph
// Teaches: adjacency matrix representation, BFS with queue, path reconstruction
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NODES 7

// Graph as adjacency matrix: graph[i][j] = weight (0 means no edge).
typedef int Graph[MAX_NODES][MAX_NODES];

// Returns path length, fills path array. Returns -1 if no path.
int bfs(Graph graph, int num_nodes, int source, int needle, int* path) {
    bool seen[MAX_NODES] = {false};
    int prev[MAX_NODES];
    memset(prev, -1, sizeof(prev));

    // Simple queue using array.
    int queue[MAX_NODES * MAX_NODES];
    int q_head = 0;
    int q_tail = 0;

    queue[q_tail++] = source;
    seen[source] = true;

    while (q_head < q_tail) {
        int curr = queue[q_head++];
        if (curr == needle) break;

        for (int i = 0; i < num_nodes; i++) {
            if (graph[curr][i] != 0 && !seen[i]) {
                seen[i] = true;
                prev[i] = curr;
                queue[q_tail++] = i;
            }
        }
    }

    // No path found.
    if (!seen[needle]) return -1;

    // Reconstruct path backwards.
    int temp[MAX_NODES];
    int len = 0;
    int curr = needle;
    while (curr != -1) {
        temp[len++] = curr;
        curr = prev[curr];
    }

    // Reverse into path.
    for (int i = 0; i < len; i++) {
        path[i] = temp[len - 1 - i];
    }
    return len;
}

int main() {
    // Graph:
    //   0 -> 1 (w3), 0 -> 2 (w1)
    //   1 -> 0 (w3), 1 -> 2 (w4), 1 -> 4 (w1)
    //   2 -> 1 (w4), 2 -> 3 (w7)
    //   3 -> 4 (w5), 3 -> 6 (w1)
    //   4 -> 1 (w1), 4 -> 3 (w5), 4 -> 5 (w2)
    //   5 -> 2 (w18), 5 -> 6 (w1)
    //   6 -> 3 (w1), 6 -> 5 (w1)
    Graph graph = {
        {0, 3, 1, 0, 0, 0, 0},  // 0
        {3, 0, 4, 0, 1, 0, 0},  // 1
        {1, 4, 0, 7, 0, 0, 0},  // 2
        {0, 0, 7, 0, 5, 0, 1},  // 3
        {0, 1, 0, 5, 0, 2, 0},  // 4
        {0, 0, 18, 0, 2, 0, 1}, // 5
        {0, 0, 0, 1, 0, 1, 0},  // 6
    };

    int path[MAX_NODES];
    int len = bfs(graph, 7, 0, 6, path);

    // BFS finds shortest hops: 0 -> 1 -> 4 -> 5 -> 6.
    assert(len == 5);
    int expected[] = {0, 1, 4, 5, 6};
    for (int i = 0; i < len; i++) assert(path[i] == expected[i]);

    int len2 = bfs(graph, 7, 6, 0, path);
    assert(len2 > 0);

    printf("All BFS graph matrix tests passed!\n");
    return 0;
}
