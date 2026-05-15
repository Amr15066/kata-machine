/// Hash Map: key-value store with separate chaining.
/// Teaches: trait bounds (Hash, Eq), hashing with DefaultHasher,
/// generic structs, Vec<Vec<(K,V)>> for bucket chains.

use std::collections::hash_map::DefaultHasher;
use std::hash::{Hash, Hasher};

const INITIAL_CAPACITY: usize = 16;

pub struct HashMap<K, V> {
    buckets: Vec<Vec<(K, V)>>,
    size: usize,
}

impl<K: Hash + Eq + Clone, V: Clone> HashMap<K, V> {
    pub fn new() -> Self {
        HashMap {
            buckets: (0..INITIAL_CAPACITY).map(|_| Vec::new()).collect(),
            size: 0,
        }
    }

    pub fn len(&self) -> usize {
        self.size
    }

    fn hash_key(&self, key: &K) -> usize {
        let mut hasher = DefaultHasher::new();
        key.hash(&mut hasher);
        (hasher.finish() as usize) % self.buckets.len()
    }

    pub fn set(&mut self, key: K, value: V) {
        let idx = self.hash_key(&key);

        // Update if key exists
        for entry in &mut self.buckets[idx] {
            if entry.0 == key {
                entry.1 = value;
                return;
            }
        }

        // Insert new
        self.buckets[idx].push((key, value));
        self.size += 1;
    }

    pub fn get(&self, key: &K) -> Option<&V> {
        let idx = self.hash_key(key);
        for entry in &self.buckets[idx] {
            if entry.0 == *key {
                return Some(&entry.1);
            }
        }
        None
    }

    pub fn delete(&mut self, key: &K) -> bool {
        let idx = self.hash_key(key);
        let bucket = &mut self.buckets[idx];

        if let Some(pos) = bucket.iter().position(|e| e.0 == *key) {
            bucket.swap_remove(pos);
            self.size -= 1;
            true
        } else {
            false
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn set_get_delete() {
        let mut m = HashMap::new();

        m.set("foo".to_string(), 55);
        assert_eq!(m.len(), 1);

        m.set("fool".to_string(), 75);
        assert_eq!(m.len(), 2);

        m.set("foolish".to_string(), 105);
        assert_eq!(m.len(), 3);

        assert_eq!(m.get(&"foo".to_string()), Some(&55));
        assert_eq!(m.get(&"fool".to_string()), Some(&75));
        assert_eq!(m.get(&"foolish".to_string()), Some(&105));
        assert_eq!(m.get(&"missing".to_string()), None);

        assert!(m.delete(&"fool".to_string()));
        assert_eq!(m.len(), 2);
        assert_eq!(m.get(&"fool".to_string()), None);

        assert!(!m.delete(&"nope".to_string()));
        assert_eq!(m.len(), 2);
    }

    #[test]
    fn update_existing() {
        let mut m = HashMap::new();
        m.set("key", 1);
        m.set("key", 2);
        assert_eq!(m.len(), 1);
        assert_eq!(m.get(&"key"), Some(&2));
    }
}
