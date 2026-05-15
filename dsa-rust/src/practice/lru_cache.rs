/// LRU Cache: Least Recently Used eviction.
/// Teaches: combining data structures, Vec-based ordering.
///
/// TODO: update() adds/refreshes, get() returns + refreshes.
/// Evict LRU (back of order list) when at capacity.

use std::collections::HashMap;

pub struct LRUCache<V> {
    capacity: usize,
    map: HashMap<String, V>,
    order: Vec<String>, // front = most recent, back = least recent
}

impl<V: Clone> LRUCache<V> {
    pub fn new(capacity: usize) -> Self {
        LRUCache {
            capacity,
            map: HashMap::new(),
            order: Vec::new(),
        }
    }

    fn touch(&mut self, key: &str) {
        // TODO: move key to front of order list (most recently used)
        // Hint: find position, remove, insert at 0
        todo!()
    }

    pub fn update(&mut self, key: &str, value: V) {
        // TODO: if exists, update value + touch
        // If new: evict LRU if at capacity, then insert + touch
        todo!()
    }

    pub fn get(&mut self, key: &str) -> Option<V> {
        // TODO: if exists, touch and return cloned value
        todo!()
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn basic_get_and_update() {
        let mut c = LRUCache::new(3);
        c.update("a", 1);
        c.update("b", 2);
        c.update("c", 3);

        assert_eq!(c.get("a"), Some(1));
        assert_eq!(c.get("b"), Some(2));
        assert_eq!(c.get("c"), Some(3));
    }

    #[test]
    fn evicts_lru() {
        let mut c = LRUCache::new(3);
        c.update("a", 1);
        c.update("b", 2);
        c.update("c", 3);

        c.get("a");
        c.get("b");
        c.get("c");

        c.update("d", 4);
        assert_eq!(c.get("a"), None);
        assert_eq!(c.get("b"), Some(2));
        assert_eq!(c.get("c"), Some(3));
        assert_eq!(c.get("d"), Some(4));
    }

    #[test]
    fn update_existing_refreshes() {
        let mut c = LRUCache::new(3);
        c.update("a", 1);
        c.update("b", 2);
        c.update("c", 3);

        c.update("a", 99);
        c.update("d", 4);

        assert_eq!(c.get("a"), Some(99));
        assert_eq!(c.get("b"), None);
        assert_eq!(c.get("d"), Some(4));
    }
}
