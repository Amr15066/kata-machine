/// LRU Cache: Least Recently Used eviction with O(n) get/put.
/// Teaches: combining data structures, Vec-based ordered tracking,
/// std::collections::HashMap for fast lookup.
///
/// A production LRU uses a doubly-linked list + hashmap for O(1).
/// Here we use Vec for ordering (simpler) — O(n) but clear to read.

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

    /// Move key to front of order list (most recently used).
    fn touch(&mut self, key: &str) {
        if let Some(pos) = self.order.iter().position(|k| k == key) {
            self.order.remove(pos);
        }
        self.order.insert(0, key.to_string());
    }

    pub fn update(&mut self, key: &str, value: V) {
        if self.map.contains_key(key) {
            // Update existing
            self.map.insert(key.to_string(), value);
            self.touch(key);
            return;
        }

        // Evict LRU if at capacity
        if self.map.len() >= self.capacity {
            if let Some(lru_key) = self.order.pop() {
                self.map.remove(&lru_key);
            }
        }

        self.map.insert(key.to_string(), value);
        self.touch(key);
    }

    pub fn get(&mut self, key: &str) -> Option<V> {
        if self.map.contains_key(key) {
            self.touch(key);
            self.map.get(key).cloned()
        } else {
            None
        }
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

        // Access a, b, c in order — after get(a), get(b), get(c):
        // order is [c, b, a] — "a" is LRU
        c.get("a");
        c.get("b");
        c.get("c");

        // Adding "d" should evict "a" (least recently used)
        c.update("d", 4);

        assert_eq!(c.get("a"), None); // evicted
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

        c.update("a", 99); // refreshes "a", now "b" is LRU
        c.update("d", 4);  // should evict "b"

        assert_eq!(c.get("a"), Some(99));
        assert_eq!(c.get("b"), None); // evicted
        assert_eq!(c.get("d"), Some(4));
    }
}
