// Practice: recursive maze solving with backtracking.
// Teaches grid traversal, recursion, and path reconstruction.
#include <array>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

struct Point {
    int x;
    int y;

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

bool walk(const std::vector<std::string>& maze,
          char wall,
          Point current,
          Point end,
          std::vector<std::vector<bool>>& seen,
          std::vector<Point>& path) {
    // TODO: implement
    // Hint: reject walls/out-of-bounds/seen cells, add current to path, recurse in four directions, and backtrack.
    (void)maze;
    (void)wall;
    (void)current;
    (void)end;
    (void)seen;
    (void)path;
    return false;
}

std::vector<Point> solve(const std::vector<std::string>& maze, char wall, Point start, Point end) {
    // TODO: implement
    // Hint: create the seen grid, call walk, and return the discovered path.
    (void)maze;
    (void)wall;
    (void)start;
    (void)end;
    return {};
}

int main() {
    const std::vector<std::string> maze{
        "#####",
        "#   #",
        "# # #",
        "#   #",
        "#####",
    };

    const std::vector<Point> expected{{1, 1}, {2, 1}, {3, 1}, {3, 2}, {3, 3}};
    const std::vector<Point> path = solve(maze, '#', Point{1, 1}, Point{3, 3});

    assert(path == expected);
    assert(solve(maze, '#', Point{1, 1}, Point{0, 0}).empty());

    std::cout << "18_maze_solver passed\n";
    return 0;
}
