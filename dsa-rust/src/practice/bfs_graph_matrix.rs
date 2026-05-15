/// BFS on Adjacency Matrix: find shortest-hop path.
/// Teaches: 2D Vec as matrix, VecDeque for BFS, path reconstruction via prev[].
///
/// graph[i][j] = weight (0 means no edge).
/// TODO: BFS from source, reconstruct path via prev[] array.

use std::collections::VecDeque;

pub fn bfs(graph: &[Vec<i32>], source: usize, needle: usize) -> Option<Vec<usize>> {
    // TODO: implement BFS with path reconstruction
    // Hint: seen[], prev[] = vec![None; n], queue
    // When you reach needle, walk prev[] backwards to build path
    todo!()
}

#[cfg(test)]
mod tests {
    use super::*;

    fn test_graph() -> Vec<Vec<i32>> {
        vec![
            vec![0, 3, 1, 0, 0, 0, 0],
            vec![3, 0, 4, 0, 1, 0, 0],
            vec![1, 4, 0, 7, 0, 0, 0],
            vec![0, 0, 7, 0, 5, 0, 1],
            vec![0, 1, 0, 5, 0, 2, 0],
            vec![0, 0,18, 0, 2, 0, 1],
            vec![0, 0, 0, 1, 0, 1, 0],
        ]
    }

    #[test]
    fn finds_path() {
        let graph = test_graph();
        let path = bfs(&graph, 0, 6);
        assert_eq!(path, Some(vec![0, 1, 4, 5, 6]));
    }

    #[test]
    fn same_node() {
        let graph = test_graph();
        let path = bfs(&graph, 0, 0);
        assert_eq!(path, Some(vec![0]));
    }
}
