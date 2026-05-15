// DFS on Adjacency List: depth-first path finding
// Teaches: adjacency list representation, recursive DFS, backtracking
//
// Implement: recursive DFS that builds a path. Backtrack on dead ends.
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NODES 7
#define MAX_EDGES 10

typedef struct { int to; int weight; } Edge;
typedef struct { Edge edges[MAX_EDGES]; int count; } AdjList;
typedef AdjList Graph[MAX_NODES];

typedef struct { int nodes[MAX_NODES]; int length; } Path;

void add_edge(Graph graph, int from, int to, int weight) {
    AdjList* adj = &graph[from];
    adj->edges[adj->count].to = to;
    adj->edges[adj->count].weight = weight;
    adj->count++;
}

bool dfs_walk(Graph graph, int curr, int needle, bool* seen, Path* path) {
    // TODO: implement recursive DFS
    // Add curr to path, check if found, mark seen, recurse neighbors, backtrack
    return false;
}

int dfs(Graph graph, int num_nodes, int source, int needle, int* result) {
    bool seen[MAX_NODES] = {false};
    Path path = { .length = 0 };
    if (dfs_walk(graph, source, needle, seen, &path)) {
        for (int i = 0; i < path.length; i++) result[i] = path.nodes[i];
        return path.length;
    }
    return -1;
}

int main(void) {
    Graph graph = {0};
    // Undirected edges
    add_edge(graph, 0, 1, 3); add_edge(graph, 1, 0, 3);
    add_edge(graph, 0, 2, 1); add_edge(graph, 2, 0, 1);
    add_edge(graph, 1, 4, 1); add_edge(graph, 4, 1, 1);
    add_edge(graph, 2, 3, 7); add_edge(graph, 3, 2, 7);
    add_edge(graph, 3, 4, 5); add_edge(graph, 4, 3, 5);
    add_edge(graph, 3, 6, 1); add_edge(graph, 6, 3, 1);
    add_edge(graph, 4, 5, 2); add_edge(graph, 5, 4, 2);
    add_edge(graph, 5, 6, 1); add_edge(graph, 6, 5, 1);

    int path[MAX_NODES];
    int len = dfs(graph, 7, 0, 6, path);

    assert(len > 0);
    assert(path[0] == 0);
    assert(path[len - 1] == 6);

    printf("All DFS graph list tests passed!\n");
    return 0;
}
