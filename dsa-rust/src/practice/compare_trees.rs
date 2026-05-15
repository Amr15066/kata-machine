/// Compare Binary Trees: structural + value equality.
/// Teaches: pattern matching on pairs of Options, recursive comparison.
///
/// TODO: Return true if both trees have same structure AND same values.

use crate::dsa::binary_tree::BinaryNode;

pub fn compare(a: Option<&BinaryNode<i32>>, b: Option<&BinaryNode<i32>>) -> bool {
    // TODO: implement
    // Hint: match (a, b) { (None, None) => true, (Some(a), Some(b)) => ..., _ => false }
    // Use .as_deref() to convert Option<&Box<T>> to Option<&T>
    todo!()
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
