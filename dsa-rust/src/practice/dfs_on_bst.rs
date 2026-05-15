/// DFS on BST: search leveraging the Binary Search Tree property.
/// Teaches: BST invariant (left < root < right), efficient O(log n) search.
///
/// TODO: If needle < value go left, if > go right, if == found.

use crate::dsa::binary_tree::BinaryNode;

pub fn dfs(node: Option<&BinaryNode<i32>>, needle: i32) -> bool {
    // TODO: implement BST search
    // Hint: match node { None => false, Some(n) => ... }
    todo!()
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::dsa::binary_tree::build_test_tree;

    #[test]
    fn finds_existing() {
        let tree = build_test_tree();
        assert!(dfs(Some(&tree), 45));
        assert!(dfs(Some(&tree), 7));
        assert!(dfs(Some(&tree), 20));
    }

    #[test]
    fn returns_false_for_missing() {
        let tree = build_test_tree();
        assert!(!dfs(Some(&tree), 69));
        assert!(!dfs(Some(&tree), 1));
    }
}
