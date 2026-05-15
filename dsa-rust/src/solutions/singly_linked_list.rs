/// Singly Linked List: forward-only linked nodes.
/// Teaches: Box ownership chains, recursive traversal via &/&mut,
/// Option combinators (as_ref, as_mut, take, map).

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
        let node = Box::new(Node {
            value,
            next: self.head.take(),
        });
        self.head = Some(node);
        self.length += 1;
    }

    pub fn append(&mut self, value: T) {
        let new_node = Box::new(Node {
            value,
            next: None,
        });

        // Walk to the last node
        let mut current = &mut self.head;
        while let Some(ref mut node) = current {
            current = &mut node.next;
        }
        *current = Some(new_node);
        self.length += 1;
    }

    pub fn insert_at(&mut self, index: usize, value: T) {
        if index == 0 {
            self.prepend(value);
            return;
        }
        if index > self.length {
            return;
        }

        let mut current = &mut self.head;
        for _ in 0..index {
            current = &mut current.as_mut().unwrap().next;
        }

        let new_node = Box::new(Node {
            value,
            next: current.take(),
        });
        *current = Some(new_node);
        self.length += 1;
    }

    pub fn get(&self, index: usize) -> Option<&T> {
        let mut current = &self.head;
        for _ in 0..index {
            current = &current.as_ref()?.next;
        }
        current.as_ref().map(|node| &node.value)
    }

    pub fn remove_at(&mut self, index: usize) -> Option<T> {
        if index >= self.length {
            return None;
        }

        let mut current = &mut self.head;
        for _ in 0..index {
            current = &mut current.as_mut()?.next;
        }

        let node = current.take()?;
        *current = node.next;
        self.length -= 1;
        Some(node.value)
    }

    pub fn remove_value(&mut self, value: &T) -> Option<T> {
        let mut current = &mut self.head;
        loop {
            match current {
                None => return None,
                Some(node) if node.value == *value => {
                    let node = current.take().unwrap();
                    *current = node.next;
                    self.length -= 1;
                    return Some(node.value);
                }
                Some(node) => {
                    current = &mut node.next;
                }
            }
        }
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
