// DFS on Adjacency List: depth-first path finding
// Teaches: adjacency list representation, recursive DFS, path building
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#define MAX_NODES 7
#define MAX_EDGES 20

typedef struct {
    int to;
    int weight;
} Edge;

typedef struct {
    Edge edges[MAX_EDGES];
    int count;
} AdjList;

typedef AdjList Graph[MAX_NODES];

// Path result.
typedef struct {
    int nodes[MAX_NODES];
    int length;
} Path;

bool dfs_walk(Graph graph, int curr, int needle, bool* seen, Path* path) {
    if (curr == needle) {
        path->nodes[path->length++] = curr;
        return true;
    }

    seen[curr] = true;
    path->nodes[path->length++] = curr;

    AdjList* adj = &graph[curr];
    for (int i = 0; i < adj->count; i++) {
        int next = adj->edges[i].to;
        if (!seen[next]) {
            if (dfs_walk(graph, next, needle, seen, path)) return true;
        }
    }

    path->length--; // backtrack
    return false;
}

int dfs(Graph graph, int num_nodes, int source, int needle, int* result) {
    (void)num_nodes;

    bool seen[MAX_NODES] = {false};
    Path path = {.length = 0};

    if (dfs_walk(graph, source, needle, seen, &path)) {
        for (int i = 0; i < path.length; i++) result[i] = path.nodes[i];
        return path.length;
    }
    return -1; // no path
}

void add_edge(Graph graph, int from, int to, int weight) {
    AdjList* adj = &graph[from];
    adj->edges[adj->count].to = to;
    adj->edges[adj->count].weight = weight;
    adj->count++;
}

int main() {
    Graph graph = {0};

    // Build same graph as matrix version.
    add_edge(graph, 0, 1, 3);
    add_edge(graph, 0, 2, 1);
    add_edge(graph, 1, 4, 1);
    add_edge(graph, 2, 3, 7);
    add_edge(graph, 3, 4, 5);
    add_edge(graph, 3, 6, 1);
    add_edge(graph, 4, 5, 2);
    add_edge(graph, 5, 6, 1);
    // Note: directed edges, so order matters for DFS.
    // Adding back edges for undirected.
    add_edge(graph, 1, 0, 3);
    add_edge(graph, 2, 0, 1);
    add_edge(graph, 4, 1, 1);
    add_edge(graph, 3, 2, 7);
    add_edge(graph, 4, 3, 5);
    add_edge(graph, 6, 3, 1);
    add_edge(graph, 5, 4, 2);
    add_edge(graph, 6, 5, 1);

    int path[MAX_NODES];
    int len = dfs(graph, 7, 0, 6, path);

    // DFS finds a path (not necessarily shortest).
    assert(len > 0);
    assert(path[0] == 0);
    assert(path[len - 1] == 6);

    printf("All DFS graph list tests passed!\n");
    return 0;
}
