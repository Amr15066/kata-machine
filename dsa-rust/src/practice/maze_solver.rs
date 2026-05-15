/// Maze Solver: recursive backtracking through a string maze.
/// Teaches: structs, derive macros, 2D grid navigation, direction arrays.
///
/// TODO: Try all 4 directions recursively. Backtrack on dead ends.

#[derive(Clone, Debug, PartialEq)]
pub struct Point {
    pub x: i32,
    pub y: i32,
}

const DX: [i32; 4] = [0, 1, 0, -1];
const DY: [i32; 4] = [-1, 0, 1, 0];

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
    // TODO: implement recursive maze walking
    // 1. Check bounds, wall, visited
    // 2. Push curr to path
    // 3. Check if we reached end
    // 4. Mark seen
    // 5. Try all 4 directions (use DX/DY arrays)
    // 6. Pop from path if dead end (backtrack)
    todo!()
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
        let maze = vec!["xxx", "x x", "xxx"];
        let path = solve(&maze, 'x', Point { x: 0, y: 0 }, Point { x: 1, y: 1 });
        assert!(path.is_empty());
    }
}
