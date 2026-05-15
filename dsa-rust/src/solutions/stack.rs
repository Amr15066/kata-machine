/// Stack: LIFO data structure backed by a singly linked list.
/// Teaches: same Box/Option patterns as Queue, but push/pop at head.

struct Node<T> {
    value: T,
    next: Option<Box<Node<T>>>,
}

pub struct Stack<T> {
    top: Option<Box<Node<T>>>,
    length: usize,
}

impl<T> Stack<T> {
    pub fn new() -> Self {
        Stack {
            top: None,
            length: 0,
        }
    }

    pub fn len(&self) -> usize {
        self.length
    }

    pub fn is_empty(&self) -> bool {
        self.length == 0
    }

    pub fn push(&mut self, value: T) {
        // New node takes ownership of old top via take()
        let node = Box::new(Node {
            value,
            next: self.top.take(),
        });
        self.top = Some(node);
        self.length += 1;
    }

    pub fn pop(&mut self) -> Option<T> {
        self.top.take().map(|node| {
            self.top = node.next;
            self.length -= 1;
            node.value
        })
    }

    pub fn peek(&self) -> Option<&T> {
        self.top.as_ref().map(|node| &node.value)
    }
}

impl<T> Drop for Stack<T> {
    fn drop(&mut self) {
        while self.pop().is_some() {}
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn lifo_order() {
        let mut s = Stack::new();
        s.push(5);
        s.push(7);
        s.push(9);

        assert_eq!(s.pop(), Some(9));
        assert_eq!(s.len(), 2);

        s.push(11);
        assert_eq!(s.pop(), Some(11));
        assert_eq!(s.pop(), Some(7));
        assert_eq!(s.peek(), Some(&5));
        assert_eq!(s.pop(), Some(5));
        assert_eq!(s.pop(), None);
        assert_eq!(s.len(), 0);
    }
}
