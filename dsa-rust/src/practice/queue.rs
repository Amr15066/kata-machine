/// Queue: FIFO data structure backed by a singly linked list.
/// Teaches: Box<T> (heap allocation), Option, take(), raw pointers for tail.
///
/// TODO: enqueue adds to tail, dequeue removes from head.

struct Node<T> {
    value: T,
    next: Option<Box<Node<T>>>,
}

pub struct Queue<T> {
    head: Option<Box<Node<T>>>,
    tail: *mut Node<T>,
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
        // TODO: create new node, link to tail, update tail pointer
        // Hint: Box::new(Node { value, next: None })
        // Use raw pointer for tail: &mut *new_node as *mut Node<T>
        todo!()
    }

    pub fn dequeue(&mut self) -> Option<T> {
        // TODO: take head, return its value, update head
        // Hint: self.head.take().map(|node| { ... })
        todo!()
    }

    pub fn peek(&self) -> Option<&T> {
        // TODO: return reference to head's value without removing
        todo!()
    }
}

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
