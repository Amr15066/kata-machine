/// Binary Tree BFS: level-order search using a VecDeque as queue.
/// Teaches: std::collections::VecDeque, BFS algorithm, borrowing in trees.

use std::collections::VecDeque;
use crate::dsa::binary_tree::BinaryNode;

pub fn bfs(root: &BinaryNode<i32>, needle: i32) -> bool {
    let mut queue: VecDeque<&BinaryNode<i32>> = VecDeque::new();
    queue.push_back(root);

    while let Some(node) = queue.pop_front() {
        if node.value == needle {
            return true;
        }
        if let Some(ref left) = node.left {
            queue.push_back(left);
        }
        if let Some(ref right) = node.right {
            queue.push_back(right);
        }
    }
    false
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
