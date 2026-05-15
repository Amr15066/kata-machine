// Maze Solver: recursive backtracking through a string maze
// Teaches: 2D navigation, direction arrays, visited tracking, backtracking
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    Point* points;
    int length;
    int capacity;
} Path;

void path_init(Path* p) {
    p->capacity = 64;
    p->length = 0;
    p->points = malloc(sizeof(Point) * p->capacity);
}

void path_push(Path* p, Point pt) {
    if (p->length == p->capacity) {
        p->capacity *= 2;
        p->points = realloc(p->points, sizeof(Point) * p->capacity);
    }
    p->points[p->length++] = pt;
}

void path_pop(Path* p) {
    if (p->length > 0) p->length--;
}

void path_free(Path* p) {
    free(p->points);
}

// Direction vectors: up, right, down, left.
int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};

bool solve_walk(const char** maze, int rows, int cols, char wall,
                bool** seen, Point curr, Point end, Path* path) {
    // Out of bounds.
    if (curr.x < 0 || curr.x >= cols || curr.y < 0 || curr.y >= rows) return false;
    // Hit wall.
    if (maze[curr.y][curr.x] == wall) return false;
    // Already visited.
    if (seen[curr.y][curr.x]) return false;

    // Found the end.
    path_push(path, curr);
    if (curr.x == end.x && curr.y == end.y) return true;

    seen[curr.y][curr.x] = true;

    for (int i = 0; i < 4; i++) {
        Point next = {curr.x + dx[i], curr.y + dy[i]};
        if (solve_walk(maze, rows, cols, wall, seen, next, end, path)) return true;
    }

    path_pop(path); // backtrack
    return false;
}

int solve(const char** maze, int rows, char wall, Point start, Point end, Point** result) {
    int cols = (int)strlen(maze[0]);

    // Allocate seen grid.
    bool** seen = malloc(sizeof(bool*) * rows);
    for (int i = 0; i < rows; i++) {
        seen[i] = calloc((size_t)cols, sizeof(bool));
    }

    Path path;
    path_init(&path);

    bool found = solve_walk(maze, rows, cols, wall, seen, start, end, &path);

    for (int i = 0; i < rows; i++) free(seen[i]);
    free(seen);

    if (!found) {
        path_free(&path);
        *result = NULL;
        return 0;
    }

    *result = path.points;
    return path.length;
}

int main() {
    const char* maze[] = {
        "xxxxxxxxxx x",
        "x        x x",
        "x        x x",
        "x xxxxxxxx x",
        "x          x",
        "x xxxxxxxxxx",
    };
    int rows = 6;
    Point start = {10, 0};
    Point end = {1, 5};

    Point* path = NULL;
    int len = solve(maze, rows, 'x', start, end, &path);

    assert(len > 0);
    assert(path[0].x == start.x && path[0].y == start.y);
    assert(path[len - 1].x == end.x && path[len - 1].y == end.y);

    free(path);
    printf("All maze solver tests passed!\n");
    return 0;
}
