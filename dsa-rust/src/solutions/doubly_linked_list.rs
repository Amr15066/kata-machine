/// Doubly Linked List using Rc<RefCell<Node<T>>> for shared ownership.
/// Teaches: Rc (reference counted pointer), RefCell (interior mutability),
/// Weak (breaking reference cycles), borrow/borrow_mut at runtime.
///
/// This is a key Rust learning moment — doubly linked lists are notoriously
/// hard in safe Rust because two nodes need to point at each other.

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
        let new_node = Rc::new(RefCell::new(Node {
            value,
            prev: None,
            next: self.head.clone(),
        }));

        match self.head.take() {
            Some(old_head) => old_head.borrow_mut().prev = Some(new_node.clone()),
            None => self.tail = Some(new_node.clone()),
        }
        self.head = Some(new_node);
        self.length += 1;
    }

    pub fn append(&mut self, value: T) {
        let new_node = Rc::new(RefCell::new(Node {
            value,
            prev: self.tail.clone(),
            next: None,
        }));

        match self.tail.take() {
            Some(old_tail) => old_tail.borrow_mut().next = Some(new_node.clone()),
            None => self.head = Some(new_node.clone()),
        }
        self.tail = Some(new_node);
        self.length += 1;
    }

    pub fn get(&self, index: usize) -> Option<T> {
        if index >= self.length {
            return None;
        }
        let mut current = self.head.clone();
        for _ in 0..index {
            let next = current.as_ref()?.borrow().next.clone();
            current = next;
        }
        current.map(|node| node.borrow().value.clone())
    }

    pub fn remove_at(&mut self, index: usize) -> Option<T> {
        if index >= self.length {
            return None;
        }

        let mut current = self.head.clone();
        for _ in 0..index {
            let next = current.as_ref()?.borrow().next.clone();
            current = next;
        }

        let node = current?;
        let prev = node.borrow().prev.clone();
        let next = node.borrow().next.clone();

        match prev.clone() {
            Some(p) => p.borrow_mut().next = next.clone(),
            None => self.head = next.clone(),
        }
        match next {
            Some(n) => n.borrow_mut().prev = prev,
            None => self.tail = prev,
        }

        // Break reference cycles on the removed node
        node.borrow_mut().prev = None;
        node.borrow_mut().next = None;
        self.length -= 1;
        Some(node.borrow().value.clone())
    }

    pub fn remove_value(&mut self, value: &T) -> Option<T> {
        let mut current = self.head.clone();
        let mut idx = 0;
        while let Some(node) = current {
            if node.borrow().value == *value {
                return self.remove_at(idx);
            }
            let next = node.borrow().next.clone();
            current = next;
            idx += 1;
        }
        None
    }
}

/// Manual Drop to break Rc cycles and avoid stack overflow
impl<T> Drop for DoublyLinkedList<T> {
    fn drop(&mut self) {
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
