/// Min Heap: array-based priority queue.
/// Teaches: implicit binary tree stored in Vec, index math for
/// parent/children, heapify up/down (bubble up/sift down).

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
        self.data.push(value);
        self.heapify_up(self.data.len() - 1);
    }

    pub fn delete(&mut self) -> Option<i32> {
        if self.data.is_empty() {
            return None;
        }
        let len = self.data.len();
        self.data.swap(0, len - 1);
        let min = self.data.pop();
        if !self.data.is_empty() {
            self.heapify_down(0);
        }
        min
    }

    fn parent(i: usize) -> usize {
        (i - 1) / 2
    }

    fn left_child(i: usize) -> usize {
        2 * i + 1
    }

    fn right_child(i: usize) -> usize {
        2 * i + 2
    }

    fn heapify_up(&mut self, mut idx: usize) {
        while idx > 0 {
            let p = Self::parent(idx);
            if self.data[idx] < self.data[p] {
                self.data.swap(idx, p);
                idx = p;
            } else {
                break;
            }
        }
    }

    fn heapify_down(&mut self, mut idx: usize) {
        loop {
            let mut smallest = idx;
            let l = Self::left_child(idx);
            let r = Self::right_child(idx);

            if l < self.data.len() && self.data[l] < self.data[smallest] {
                smallest = l;
            }
            if r < self.data.len() && self.data[r] < self.data[smallest] {
                smallest = r;
            }

            if smallest == idx {
                break;
            }
            self.data.swap(idx, smallest);
            idx = smallest;
        }
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
