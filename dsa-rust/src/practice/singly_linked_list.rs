/// Singly Linked List: forward-only linked nodes.
/// Teaches: Box ownership chains, Option combinators (as_ref, as_mut, take).
///
/// TODO: Implement all list operations. Watch edge cases at head/tail.

type Link<T> = Option<Box<Node<T>>>;

struct Node<T> {
    value: T,
    next: Link<T>,
}

pub struct SinglyLinkedList<T> {
    head: Link<T>,
    length: usize,
}

impl<T: PartialEq> SinglyLinkedList<T> {
    pub fn new() -> Self {
        SinglyLinkedList {
            head: None,
            length: 0,
        }
    }

    pub fn len(&self) -> usize {
        self.length
    }

    pub fn prepend(&mut self, value: T) {
        // TODO: new node with next = old head
        // Hint: self.head.take() moves the old head out
        todo!()
    }

    pub fn append(&mut self, value: T) {
        // TODO: walk to end, set last node's next = new node
        // Hint: use &mut self.head then walk &mut node.next
        todo!()
    }

    pub fn get(&self, index: usize) -> Option<&T> {
        // TODO: walk to index, return reference to value
        todo!()
    }

    pub fn remove_at(&mut self, index: usize) -> Option<T> {
        // TODO: walk to position, unlink node, return its value
        todo!()
    }

    pub fn remove_value(&mut self, value: &T) -> Option<T> {
        // TODO: find node with matching value, unlink it
        todo!()
    }
}

impl<T> Drop for SinglyLinkedList<T> {
    fn drop(&mut self) {
        let mut current = self.head.take();
        while let Some(mut node) = current {
            current = node.next.take();
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn append_get_remove() {
        let mut list = SinglyLinkedList::new();
        list.append(5);
        list.append(7);
        list.append(9);

        assert_eq!(list.get(2), Some(&9));
        assert_eq!(list.remove_at(1), Some(7));
        assert_eq!(list.len(), 2);

        list.append(11);
        assert_eq!(list.remove_at(1), Some(9));
        assert!(list.remove_value(&9).is_none());
        assert_eq!(list.remove_at(0), Some(5));
        assert_eq!(list.remove_at(0), Some(11));
        assert_eq!(list.len(), 0);
    }

    #[test]
    fn prepend_and_get() {
        let mut list = SinglyLinkedList::new();
        list.prepend(5);
        list.prepend(7);
        list.prepend(9);

        assert_eq!(list.get(0), Some(&9));
        assert_eq!(list.get(1), Some(&7));
        assert_eq!(list.get(2), Some(&5));
    }
}
