/// Stack: LIFO data structure backed by a singly linked list.
/// Teaches: same Box/Option patterns as Queue, but push/pop at head.
///
/// TODO: push adds new node as head, pop removes head.

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
        // TODO: new node takes old top via self.top.take()
        todo!()
    }

    pub fn pop(&mut self) -> Option<T> {
        // TODO: take top, restore next as new top, return value
        todo!()
    }

    pub fn peek(&self) -> Option<&T> {
        // TODO: return reference to top value
        todo!()
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
