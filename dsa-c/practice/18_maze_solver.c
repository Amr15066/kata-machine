// Maze Solver: recursive backtracking through a string maze
// Teaches: 2D navigation, direction arrays, visited tracking, backtracking
//
// Implement: try all 4 directions recursively. Backtrack on dead ends.
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

typedef struct { int x, y; } Point;

typedef struct {
    Point* points;
    int length;
    int capacity;
} Path;

void path_init(Path* p) { p->capacity = 64; p->length = 0; p->points = malloc(sizeof(Point) * 64); }
void path_push(Path* p, Point pt) {
    if (p->length == p->capacity) { p->capacity *= 2; p->points = realloc(p->points, sizeof(Point) * p->capacity); }
    p->points[p->length++] = pt;
}
void path_pop(Path* p) { if (p->length > 0) p->length--; }
void path_free(Path* p) { free(p->points); }

// Direction vectors: up, right, down, left
int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};

bool solve_walk(const char** maze, int rows, int cols, char wall,
                bool** seen, Point curr, Point end, Path* path) {
    // TODO: implement recursive maze solving
    // Check bounds, wall, visited. Push to path. Try 4 directions. Backtrack.
    return false;
}

int solve(const char** maze, int rows, char wall, Point start, Point end, Point** result) {
    int cols = (int)strlen(maze[0]);
    bool** seen = malloc(sizeof(bool*) * rows);
    for (int i = 0; i < rows; i++) seen[i] = calloc(cols, sizeof(bool));

    Path path;
    path_init(&path);
    bool found = solve_walk(maze, rows, cols, wall, seen, start, end, &path);

    for (int i = 0; i < rows; i++) free(seen[i]);
    free(seen);

    if (!found) { path_free(&path); *result = NULL; return 0; }
    *result = path.points;
    return path.length;
}

int main(void) {
    const char* maze[] = {
        "xxxxxxxxxx x",
        "x        x x",
        "x        x x",
        "x xxxxxxxx x",
        "x          x",
        "x xxxxxxxxxx",
    };
    Point start = {10, 0};
    Point end = {1, 5};

    Point* path = NULL;
    int len = solve(maze, 6, 'x', start, end, &path);

    assert(len > 0);
    assert(path[0].x == 10 && path[0].y == 0);
    assert(path[len-1].x == 1 && path[len-1].y == 5);

    free(path);
    printf("All maze solver tests passed!\n");
    return 0;
}
