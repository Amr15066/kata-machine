/// Binary Tree BFS: level-order search using a VecDeque as queue.
/// Teaches: std::collections::VecDeque, BFS algorithm, borrowing in trees.
///
/// TODO: Use a queue to visit nodes level by level.

use std::collections::VecDeque;
use crate::dsa::binary_tree::BinaryNode;

pub fn bfs(root: &BinaryNode<i32>, needle: i32) -> bool {
    // TODO: implement BFS
    // Hint: let mut queue = VecDeque::new(); queue.push_back(root);
    // Then loop: pop_front, check value, push children
    todo!()
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::dsa::binary_tree::build_test_tree;

    #[test]
    fn finds_existing() {
        let tree = build_test_tree();
        assert!(bfs(&tree, 45));
        assert!(bfs(&tree, 7));
        assert!(bfs(&tree, 20));
    }

    #[test]
    fn returns_false_for_missing() {
        let tree = build_test_tree();
        assert!(!bfs(&tree, 69));
        assert!(!bfs(&tree, 0));
    }
}
