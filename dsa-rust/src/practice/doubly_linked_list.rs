/// Doubly Linked List using Rc<RefCell<Node<T>>>.
/// Teaches: Rc (reference counting), RefCell (interior mutability),
/// runtime borrow checking. Doubly linked lists are notoriously hard
/// in safe Rust — this is a key learning moment.
///
/// TODO: Implement all operations. Remember to update both prev/next
/// and break Rc cycles on removal.

use std::cell::RefCell;
use std::rc::Rc;

type Link<T> = Option<Rc<RefCell<Node<T>>>>;

struct Node<T> {
    value: T,
    prev: Link<T>,
    next: Link<T>,
}

pub struct DoublyLinkedList<T> {
    head: Link<T>,
    tail: Link<T>,
    length: usize,
}

impl<T: Clone + PartialEq> DoublyLinkedList<T> {
    pub fn new() -> Self {
        DoublyLinkedList {
            head: None,
            tail: None,
            length: 0,
        }
    }

    pub fn len(&self) -> usize {
        self.length
    }

    pub fn prepend(&mut self, value: T) {
        // TODO: create Rc<RefCell<Node>>, link to old head
        // Hint: Rc::new(RefCell::new(Node { value, prev: None, next: self.head.clone() }))
        todo!()
    }

    pub fn append(&mut self, value: T) {
        // TODO: create node, link to old tail
        todo!()
    }

    pub fn get(&self, index: usize) -> Option<T> {
        // TODO: walk to index, return cloned value
        // Hint: node.borrow().next.clone() to walk
        todo!()
    }

    pub fn remove_at(&mut self, index: usize) -> Option<T> {
        // TODO: walk to node, fix prev/next links, break Rc cycles
        todo!()
    }

    pub fn remove_value(&mut self, value: &T) -> Option<T> {
        // TODO: find node by value, delegate to remove logic
        todo!()
    }
}

impl<T> Drop for DoublyLinkedList<T> {
    fn drop(&mut self) {
        // Break Rc cycles to avoid memory leaks
        let mut current = self.head.take();
        while let Some(node) = current {
            let next = node.borrow_mut().next.take();
            node.borrow_mut().prev = None;
            current = next;
        }
        self.tail = None;
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn append_get_remove() {
        let mut list = DoublyLinkedList::new();
        list.append(5);
        list.append(7);
        list.append(9);

        assert_eq!(list.get(2), Some(9));
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
        let mut list = DoublyLinkedList::new();
        list.prepend(5);
        list.prepend(7);
        list.prepend(9);

        assert_eq!(list.get(0), Some(9));
        assert_eq!(list.get(1), Some(7));
        assert_eq!(list.get(2), Some(5));
    }
}
