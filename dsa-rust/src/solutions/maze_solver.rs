/// Maze Solver: recursive backtracking through a string maze.
/// Teaches: structs, derive macros, 2D grid navigation, direction arrays,
/// mutable 2D Vec for visited tracking.

#[derive(Clone, Debug, PartialEq)]
pub struct Point {
    pub x: i32,
    pub y: i32,
}

/// Solve a maze represented as lines of characters.
/// Returns path from start to end, or empty vec if no path.
pub fn solve(maze: &[&str], wall: char, start: Point, end: Point) -> Vec<Point> {
    let rows = maze.len() as i32;
    let cols = maze[0].len() as i32;
    let mut seen = vec![vec![false; cols as usize]; rows as usize];
    let mut path = Vec::new();

    if walk(maze, wall, rows, cols, &start, &end, &mut seen, &mut path) {
        path
    } else {
        Vec::new()
    }
}

// Direction vectors: up, right, down, left
const DX: [i32; 4] = [0, 1, 0, -1];
const DY: [i32; 4] = [-1, 0, 1, 0];

fn walk(
    maze: &[&str],
    wall: char,
    rows: i32,
    cols: i32,
    curr: &Point,
    end: &Point,
    seen: &mut [Vec<bool>],
    path: &mut Vec<Point>,
) -> bool {
    // Out of bounds
    if curr.x < 0 || curr.x >= cols || curr.y < 0 || curr.y >= rows {
        return false;
    }

    let (uy, ux) = (curr.y as usize, curr.x as usize);

    // Hit wall
    if maze[uy].as_bytes()[ux] == wall as u8 {
        return false;
    }

    // Already visited
    if seen[uy][ux] {
        return false;
    }

    // Add to path
    path.push(curr.clone());

    // Found the end
    if curr == end {
        return true;
    }

    seen[uy][ux] = true;

    // Try all 4 directions
    for i in 0..4 {
        let next = Point {
            x: curr.x + DX[i],
            y: curr.y + DY[i],
        };
        if walk(maze, wall, rows, cols, &next, end, seen, path) {
            return true;
        }
    }

    path.pop(); // backtrack
    false
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn solves_maze() {
        let maze = vec![
            "xxxxxxxxxx x",
            "x        x x",
            "x        x x",
            "x xxxxxxxx x",
            "x          x",
            "x xxxxxxxxxx",
        ];

        let start = Point { x: 10, y: 0 };
        let end = Point { x: 1, y: 5 };

        let path = solve(&maze, 'x', start.clone(), end.clone());

        assert!(!path.is_empty());
        assert_eq!(path[0], start);
        assert_eq!(*path.last().unwrap(), end);
    }

    #[test]
    fn no_path() {
        let maze = vec![
            "xxx",
            "x x",
            "xxx",
        ];
        let path = solve(&maze, 'x', Point { x: 0, y: 0 }, Point { x: 1, y: 1 });
        // Start is on a wall, so no path
        assert!(path.is_empty());
    }
}
