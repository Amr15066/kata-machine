/// Queue: FIFO data structure backed by a singly linked list.
/// Teaches: Box<T> (heap allocation), Option, generic structs, take().

struct Node<T> {
    value: T,
    next: Option<Box<Node<T>>>,
}

pub struct Queue<T> {
    head: Option<Box<Node<T>>>,
    tail: *mut Node<T>, // raw pointer to tail — safe usage pattern
    length: usize,
}

impl<T> Queue<T> {
    pub fn new() -> Self {
        Queue {
            head: None,
            tail: std::ptr::null_mut(),
            length: 0,
        }
    }

    pub fn len(&self) -> usize {
        self.length
    }

    pub fn is_empty(&self) -> bool {
        self.length == 0
    }

    pub fn enqueue(&mut self, value: T) {
        let mut new_node = Box::new(Node { value, next: None });
        let raw: *mut Node<T> = &mut *new_node;

        if self.tail.is_null() {
            self.head = Some(new_node);
        } else {
            // Safety: tail always points to a valid node we own
            unsafe { (*self.tail).next = Some(new_node) };
        }
        self.tail = raw;
        self.length += 1;
    }

    pub fn dequeue(&mut self) -> Option<T> {
        // take() moves the Option out, leaving None — a key Rust pattern
        self.head.take().map(|node| {
            self.head = node.next;
            if self.head.is_none() {
                self.tail = std::ptr::null_mut();
            }
            self.length -= 1;
            node.value
        })
    }

    pub fn peek(&self) -> Option<&T> {
        self.head.as_ref().map(|node| &node.value)
    }
}

// Drop cleans up automatically since Box<Node<T>> is recursive.
// But a long list could overflow the stack with recursive drops,
// so we do it iteratively.
impl<T> Drop for Queue<T> {
    fn drop(&mut self) {
        while self.dequeue().is_some() {}
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn fifo_order() {
        let mut q = Queue::new();
        q.enqueue(5);
        q.enqueue(7);
        q.enqueue(9);

        assert_eq!(q.dequeue(), Some(5));
        assert_eq!(q.len(), 2);

        q.enqueue(11);
        assert_eq!(q.dequeue(), Some(7));
        assert_eq!(q.dequeue(), Some(9));
        assert_eq!(q.peek(), Some(&11));
        assert_eq!(q.dequeue(), Some(11));
        assert_eq!(q.dequeue(), None);
        assert_eq!(q.len(), 0);
    }

    #[test]
    fn enqueue_after_empty() {
        let mut q = Queue::new();
        q.enqueue(1);
        assert_eq!(q.dequeue(), Some(1));
        assert_eq!(q.dequeue(), None);

        q.enqueue(69);
        assert_eq!(q.peek(), Some(&69));
        assert_eq!(q.len(), 1);
    }
}
