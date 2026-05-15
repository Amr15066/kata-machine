/// Compare Binary Trees: structural + value equality.
/// Teaches: pattern matching on pairs of Options, recursive comparison.

use crate::dsa::binary_tree::BinaryNode;

pub fn compare(
    a: Option<&BinaryNode<i32>>,
    b: Option<&BinaryNode<i32>>,
) -> bool {
    match (a, b) {
        // Both None — structurally equal at this point
        (None, None) => true,
        // One is None, other isn't — different structure
        (None, Some(_)) | (Some(_), None) => false,
        // Both Some — compare value and recurse
        (Some(a), Some(b)) => {
            a.value == b.value
                && compare(a.left.as_deref(), b.left.as_deref())
                && compare(a.right.as_deref(), b.right.as_deref())
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::dsa::binary_tree::{BinaryNode, build_test_tree};

    #[test]
    fn same_trees_are_equal() {
        let t1 = build_test_tree();
        let t2 = build_test_tree();
        assert!(compare(Some(&t1), Some(&t2)));
    }

    #[test]
    fn different_trees_not_equal() {
        let t1 = build_test_tree();
        // Different tree
        let t2 = Box::new(BinaryNode::new(99));
        assert!(!compare(Some(&t1), Some(&t2)));
    }

    #[test]
    fn null_comparisons() {
        let t1 = build_test_tree();
        assert!(!compare(Some(&t1), None));
        assert!(!compare(None, Some(&t1)));
        assert!(compare(None::<&BinaryNode<i32>>, None));
    }
}
