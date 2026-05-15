/// Binary Tree Traversals: pre-order, in-order, post-order DFS.
/// Teaches: recursive enums, Box for heap allocation, pattern matching
/// on Option<Box<T>>, collecting results into Vec.
///
/// TODO: Implement three traversals:
///   pre_order:  root, left, right
///   in_order:   left, root, right
///   post_order: left, right, root

pub struct BinaryNode<T> {
    pub value: T,
    pub left: Option<Box<BinaryNode<T>>>,
    pub right: Option<Box<BinaryNode<T>>>,
}

impl<T> BinaryNode<T> {
    pub fn new(value: T) -> Self {
        BinaryNode { value, left: None, right: None }
    }

    pub fn with_children(
        value: T,
        left: Option<Box<BinaryNode<T>>>,
        right: Option<Box<BinaryNode<T>>>,
    ) -> Self {
        BinaryNode { value, left, right }
    }
}

pub fn pre_order<T: Clone>(node: &Option<Box<BinaryNode<T>>>) -> Vec<T> {
    let mut result = Vec::new();
    pre_order_walk(node, &mut result);
    result
}

fn pre_order_walk<T: Clone>(node: &Option<Box<BinaryNode<T>>>, result: &mut Vec<T>) {
    // TODO: visit root, then left, then right
    // Hint: if let Some(n) = node { ... }
    todo!()
}

pub fn in_order<T: Clone>(node: &Option<Box<BinaryNode<T>>>) -> Vec<T> {
    let mut result = Vec::new();
    in_order_walk(node, &mut result);
    result
}

fn in_order_walk<T: Clone>(node: &Option<Box<BinaryNode<T>>>, result: &mut Vec<T>) {
    // TODO: left, then root, then right
    todo!()
}

pub fn post_order<T: Clone>(node: &Option<Box<BinaryNode<T>>>) -> Vec<T> {
    let mut result = Vec::new();
    post_order_walk(node, &mut result);
    result
}

fn post_order_walk<T: Clone>(node: &Option<Box<BinaryNode<T>>>, result: &mut Vec<T>) {
    // TODO: left, then right, then root
    todo!()
}

/// Test tree:
///        20
///       /  \
///     10    50
///    / \   /  \
///   5  15 30  100
///    \   / \
///     7 29 45
pub fn build_test_tree() -> Box<BinaryNode<i32>> {
    Box::new(BinaryNode::with_children(
        20,
        Some(Box::new(BinaryNode::with_children(
            10,
            Some(Box::new(BinaryNode::with_children(5, None, Some(Box::new(BinaryNode::new(7)))))),
            Some(Box::new(BinaryNode::new(15))),
        ))),
        Some(Box::new(BinaryNode::with_children(
            50,
            Some(Box::new(BinaryNode::with_children(
                30,
                Some(Box::new(BinaryNode::new(29))),
                Some(Box::new(BinaryNode::new(45))),
            ))),
            Some(Box::new(BinaryNode::new(100))),
        ))),
    ))
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_pre_order() {
        let tree = Some(build_test_tree());
        assert_eq!(pre_order(&tree), vec![20, 10, 5, 7, 15, 50, 30, 29, 45, 100]);
    }

    #[test]
    fn test_in_order() {
        let tree = Some(build_test_tree());
        assert_eq!(in_order(&tree), vec![5, 7, 10, 15, 20, 29, 30, 45, 50, 100]);
    }

    #[test]
    fn test_post_order() {
        let tree = Some(build_test_tree());
        assert_eq!(post_order(&tree), vec![7, 5, 15, 10, 29, 45, 30, 100, 50, 20]);
    }
}
