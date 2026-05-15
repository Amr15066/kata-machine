/// ArrayList: dynamic array with manual growth.
/// Teaches: Vec internals — capacity vs length, amortized O(1) append.
///
/// TODO: Implement list operations. For learning, think about how
/// Vec::push, Vec::insert, Vec::remove work under the hood.

pub struct ArrayList<T> {
    data: Vec<T>,
}

impl<T: Clone + PartialEq> ArrayList<T> {
    pub fn new() -> Self {
        ArrayList {
            data: Vec::with_capacity(4),
        }
    }

    pub fn len(&self) -> usize {
        self.data.len()
    }

    pub fn append(&mut self, value: T) {
        // TODO: add to end
        todo!()
    }

    pub fn prepend(&mut self, value: T) {
        // TODO: insert at index 0 (shifts all elements right)
        todo!()
    }

    pub fn get(&self, index: usize) -> Option<&T> {
        // TODO: bounds-checked access
        todo!()
    }

    pub fn remove_at(&mut self, index: usize) -> Option<T> {
        // TODO: remove element at index, shift left
        todo!()
    }

    pub fn remove_value(&mut self, value: &T) -> Option<T> {
        // TODO: find first match, remove it
        // Hint: .iter().position(|x| x == value)
        todo!()
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn append_get_remove() {
        let mut list = ArrayList::new();
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
        let mut list = ArrayList::new();
        list.prepend(5);
        list.prepend(7);
        list.prepend(9);

        assert_eq!(list.get(0), Some(&9));
        assert_eq!(list.get(1), Some(&7));
        assert_eq!(list.get(2), Some(&5));
    }
}
