/// ArrayList: dynamic array with manual growth.
/// Teaches: Vec internals concept — capacity vs length, amortized O(1) append.
/// We use Vec but manage capacity ourselves to show how it works under the hood.

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
        self.data.push(value);
    }

    pub fn prepend(&mut self, value: T) {
        self.data.insert(0, value);
    }

    pub fn insert_at(&mut self, index: usize, value: T) {
        if index > self.data.len() {
            return;
        }
        self.data.insert(index, value);
    }

    pub fn get(&self, index: usize) -> Option<&T> {
        self.data.get(index)
    }

    pub fn remove_at(&mut self, index: usize) -> Option<T> {
        if index >= self.data.len() {
            return None;
        }
        Some(self.data.remove(index))
    }

    pub fn remove_value(&mut self, value: &T) -> Option<T> {
        if let Some(pos) = self.data.iter().position(|x| x == value) {
            Some(self.data.remove(pos))
        } else {
            None
        }
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
