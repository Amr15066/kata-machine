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
    if (current.x < 0 || current.y < 0 ||
        current.y >= static_cast<int>(maze.size()) ||
        current.x >= static_cast<int>(maze[static_cast<std::size_t>(current.y)].size())) {
        return false;
    }
    if (maze[static_cast<std::size_t>(current.y)][static_cast<std::size_t>(current.x)] == wall) {
        return false;
    }
    if (seen[static_cast<std::size_t>(current.y)][static_cast<std::size_t>(current.x)]) {
        return false;
    }

    seen[static_cast<std::size_t>(current.y)][static_cast<std::size_t>(current.x)] = true;
    path.push_back(current);

    if (current == end) {
        return true;
    }

    const std::array<Point, 4> directions{{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}};
    for (const Point& direction : directions) {
        Point next{current.x + direction.x, current.y + direction.y};
        if (walk(maze, wall, next, end, seen, path)) {
            return true;
        }
    }

    path.pop_back();
    return false;
}

std::vector<Point> solve(const std::vector<std::string>& maze, char wall, Point start, Point end) {
    std::vector<Point> path;
    std::vector<std::vector<bool>> seen(maze.size());
    for (std::size_t y = 0; y < maze.size(); ++y) {
        seen[y] = std::vector<bool>(maze[y].size(), false);
    }
    walk(maze, wall, start, end, seen, path);
    return path;
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
