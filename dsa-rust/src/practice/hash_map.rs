/// Hash Map: key-value store with separate chaining.
/// Teaches: Hash + Eq trait bounds, DefaultHasher, generics,
/// Vec<Vec<(K,V)>> bucket chains.
///
/// TODO: Implement hash function, set, get, delete.
/// Do NOT use std::collections::HashMap — build your own!

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
        // TODO: hash the key and map to a bucket index
        // Hint: DefaultHasher::new(), key.hash(&mut hasher), hasher.finish()
        todo!()
    }

    pub fn set(&mut self, key: K, value: V) {
        // TODO: hash key, update if exists, else insert new entry
        todo!()
    }

    pub fn get(&self, key: &K) -> Option<&V> {
        // TODO: hash key, walk chain, return value if found
        todo!()
    }

    pub fn delete(&mut self, key: &K) -> bool {
        // TODO: hash key, find and remove from chain
        // Hint: bucket.swap_remove(pos) is O(1)
        todo!()
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
        m.set("foolish".to_string(), 105);

        assert_eq!(m.get(&"foo".to_string()), Some(&55));
        assert_eq!(m.get(&"fool".to_string()), Some(&75));
        assert_eq!(m.get(&"foolish".to_string()), Some(&105));
        assert_eq!(m.get(&"missing".to_string()), None);

        assert!(m.delete(&"fool".to_string()));
        assert_eq!(m.len(), 2);
        assert_eq!(m.get(&"fool".to_string()), None);

        assert!(!m.delete(&"nope".to_string()));
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
