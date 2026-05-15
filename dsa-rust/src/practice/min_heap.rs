/// Min Heap: array-based priority queue.
/// Teaches: implicit binary tree in Vec, heapify up/down.
///
/// Index math: parent = (i-1)/2, left = 2i+1, right = 2i+2
/// TODO: insert adds to end + heapify up. delete swaps root + heapify down.

pub struct MinHeap {
    data: Vec<i32>,
}

impl MinHeap {
    pub fn new() -> Self {
        MinHeap { data: Vec::new() }
    }

    pub fn len(&self) -> usize {
        self.data.len()
    }

    pub fn is_empty(&self) -> bool {
        self.data.is_empty()
    }

    pub fn insert(&mut self, value: i32) {
        // TODO: push to end, then heapify up
        todo!()
    }

    pub fn delete(&mut self) -> Option<i32> {
        // TODO: swap first and last, pop last, heapify down, return min
        todo!()
    }

    fn heapify_up(&mut self, mut idx: usize) {
        // TODO: while parent > current, swap up
        todo!()
    }

    fn heapify_down(&mut self, mut idx: usize) {
        // TODO: while smallest child < current, swap down
        todo!()
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn insert_and_delete_in_order() {
        let mut h = MinHeap::new();
        h.insert(5);
        h.insert(3);
        h.insert(69);
        h.insert(420);
        h.insert(4);
        h.insert(1);
        h.insert(8);
        h.insert(7);

        assert_eq!(h.len(), 8);
        assert_eq!(h.delete(), Some(1));
        assert_eq!(h.delete(), Some(3));
        assert_eq!(h.delete(), Some(4));
        assert_eq!(h.delete(), Some(5));
        assert_eq!(h.len(), 4);
        assert_eq!(h.delete(), Some(7));
        assert_eq!(h.delete(), Some(8));
        assert_eq!(h.delete(), Some(69));
        assert_eq!(h.delete(), Some(420));
        assert_eq!(h.len(), 0);
    }
}
