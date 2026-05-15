/// BFS on Adjacency Matrix: find shortest-hop path.
/// Teaches: 2D Vec as matrix, VecDeque for BFS queue, path reconstruction
/// via prev[] array.

use std::collections::VecDeque;

/// graph[i][j] = weight (0 means no edge).
/// Returns the path as a list of node indices, or None if unreachable.
pub fn bfs(graph: &[Vec<i32>], source: usize, needle: usize) -> Option<Vec<usize>> {
    let n = graph.len();
    let mut seen = vec![false; n];
    let mut prev = vec![None; n];

    let mut queue = VecDeque::new();
    queue.push_back(source);
    seen[source] = true;

    while let Some(curr) = queue.pop_front() {
        if curr == needle {
            // Reconstruct path
            let mut path = Vec::new();
            let mut at = Some(needle);
            while let Some(node) = at {
                path.push(node);
                at = prev[node];
            }
            path.reverse();
            return Some(path);
        }

        for i in 0..n {
            if graph[curr][i] != 0 && !seen[i] {
                seen[i] = true;
                prev[i] = Some(curr);
                queue.push_back(i);
            }
        }
    }

    None
}

#[cfg(test)]
mod tests {
    use super::*;

    fn test_graph() -> Vec<Vec<i32>> {
        // 7-node graph (same as TypeScript version)
        vec![
            vec![0, 3, 1, 0, 0, 0, 0], // 0
            vec![3, 0, 4, 0, 1, 0, 0], // 1
            vec![1, 4, 0, 7, 0, 0, 0], // 2
            vec![0, 0, 7, 0, 5, 0, 1], // 3
            vec![0, 1, 0, 5, 0, 2, 0], // 4
            vec![0, 0,18, 0, 2, 0, 1], // 5
            vec![0, 0, 0, 1, 0, 1, 0], // 6
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
