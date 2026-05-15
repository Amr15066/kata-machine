/// DFS on Adjacency List: depth-first path finding.
/// Teaches: adjacency list as Vec<Vec<(usize, i32)>>, recursive DFS,
/// mutable visited tracking, backtracking path construction.

/// graph[i] = vec of (neighbor, weight) pairs.
pub fn dfs(
    graph: &[Vec<(usize, i32)>],
    source: usize,
    needle: usize,
) -> Option<Vec<usize>> {
    let mut seen = vec![false; graph.len()];
    let mut path = Vec::new();

    if dfs_walk(graph, source, needle, &mut seen, &mut path) {
        Some(path)
    } else {
        None
    }
}

fn dfs_walk(
    graph: &[Vec<(usize, i32)>],
    curr: usize,
    needle: usize,
    seen: &mut [bool],
    path: &mut Vec<usize>,
) -> bool {
    if curr == needle {
        path.push(curr);
        return true;
    }

    seen[curr] = true;
    path.push(curr);

    for &(neighbor, _weight) in &graph[curr] {
        if !seen[neighbor] && dfs_walk(graph, neighbor, needle, seen, path) {
            return true;
        }
    }

    path.pop(); // backtrack
    false
}

#[cfg(test)]
mod tests {
    use super::*;

    fn test_graph() -> Vec<Vec<(usize, i32)>> {
        // Same 7-node graph, undirected (edges in both directions)
        vec![
            vec![(1, 3), (2, 1)],           // 0
            vec![(0, 3), (2, 4), (4, 1)],   // 1
            vec![(0, 1), (1, 4), (3, 7)],   // 2
            vec![(2, 7), (4, 5), (6, 1)],   // 3
            vec![(1, 1), (3, 5), (5, 2)],   // 4
            vec![(2, 18), (4, 2), (6, 1)],  // 5
            vec![(3, 1), (5, 1)],           // 6
        ]
    }

    #[test]
    fn finds_a_path() {
        let graph = test_graph();
        let path = dfs(&graph, 0, 6).expect("should find a path");
        assert_eq!(path[0], 0);
        assert_eq!(*path.last().unwrap(), 6);
        assert!(path.len() >= 2);
    }

    #[test]
    fn no_path_to_disconnected() {
        // Node 7 is disconnected
        let mut graph = test_graph();
        graph.push(vec![]); // node 7, no edges
        assert!(dfs(&graph, 0, 7).is_none());
    }
}
