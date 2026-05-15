// BFS on Adjacency Matrix: find shortest-hop path
// Teaches: adjacency matrix, BFS with queue, path reconstruction via prev[]
//
// Implement: standard BFS. Track prev[] to reconstruct path.
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NODES 7

typedef int Graph[MAX_NODES][MAX_NODES];

// Returns path length, fills path array. Returns -1 if no path.
int bfs(Graph graph, int num_nodes, int source, int needle, int* path) {
    // TODO: implement BFS with path reconstruction
    // Hint: use seen[], prev[], and a queue (simple array with head/tail)
    return -1;
}

int main(void) {
    Graph graph = {
        {0, 3, 1, 0, 0, 0, 0},
        {3, 0, 4, 0, 1, 0, 0},
        {1, 4, 0, 7, 0, 0, 0},
        {0, 0, 7, 0, 5, 0, 1},
        {0, 1, 0, 5, 0, 2, 0},
        {0, 0,18, 0, 2, 0, 1},
        {0, 0, 0, 1, 0, 1, 0},
    };

    int path[MAX_NODES];
    int len = bfs(graph, 7, 0, 6, path);

    assert(len == 5);
    int expected[] = {0, 1, 4, 5, 6};
    for (int i = 0; i < len; i++) assert(path[i] == expected[i]);

    printf("All BFS graph matrix tests passed!\n");
    return 0;
}
