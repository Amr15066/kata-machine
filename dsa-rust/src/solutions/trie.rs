/// Trie: prefix tree for string storage and search.
/// Teaches: recursive structs with Box, HashMap<char, Box<Node>>,
/// String building during traversal, recursive collect pattern.

use std::collections::HashMap;

struct TrieNode {
    children: HashMap<char, Box<TrieNode>>,
    is_end: bool,
}

impl TrieNode {
    fn new() -> Self {
        TrieNode {
            children: HashMap::new(),
            is_end: false,
        }
    }
}

pub struct Trie {
    root: TrieNode,
}

impl Trie {
    pub fn new() -> Self {
        Trie {
            root: TrieNode::new(),
        }
    }

    pub fn insert(&mut self, word: &str) {
        let mut current = &mut self.root;
        for ch in word.chars() {
            current = current
                .children
                .entry(ch)
                .or_insert_with(|| Box::new(TrieNode::new()));
        }
        current.is_end = true;
    }

    pub fn delete(&mut self, word: &str) {
        let chars: Vec<char> = word.chars().collect();
        Self::delete_helper(&mut self.root, &chars, 0);
    }

    /// Returns true if the node can be removed by parent.
    fn delete_helper(node: &mut TrieNode, chars: &[char], depth: usize) -> bool {
        if depth == chars.len() {
            if !node.is_end {
                return false;
            }
            node.is_end = false;
            return node.children.is_empty();
        }

        let ch = chars[depth];
        let should_remove = if let Some(child) = node.children.get_mut(&ch) {
            Self::delete_helper(child, chars, depth + 1)
        } else {
            false
        };

        if should_remove {
            node.children.remove(&ch);
            return !node.is_end && node.children.is_empty();
        }
        false
    }

    /// Find all words with the given prefix.
    pub fn find(&self, prefix: &str) -> Vec<String> {
        let mut current = &self.root;
        for ch in prefix.chars() {
            match current.children.get(&ch) {
                Some(child) => current = child,
                None => return Vec::new(),
            }
        }

        let mut results = Vec::new();
        let mut buffer = prefix.to_string();
        Self::collect(current, &mut buffer, &mut results);
        results
    }

    fn collect(node: &TrieNode, buffer: &mut String, results: &mut Vec<String>) {
        if node.is_end {
            results.push(buffer.clone());
        }

        // Sort keys for deterministic output
        let mut keys: Vec<&char> = node.children.keys().collect();
        keys.sort();

        for &ch in &keys {
            let child = &node.children[ch];
            buffer.push(*ch);
            Self::collect(child, buffer, results);
            buffer.pop();
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn find_by_prefix() {
        let mut t = Trie::new();
        t.insert("foo");
        t.insert("fool");
        t.insert("foolish");
        t.insert("bar");

        let mut results = t.find("fo");
        results.sort();
        assert_eq!(results, vec!["foo", "fool", "foolish"]);
    }

    #[test]
    fn delete_removes_word() {
        let mut t = Trie::new();
        t.insert("foo");
        t.insert("fool");
        t.insert("foolish");

        t.delete("fool");

        let mut results = t.find("fo");
        results.sort();
        assert_eq!(results, vec!["foo", "foolish"]);
    }

    #[test]
    fn find_empty_prefix() {
        let mut t = Trie::new();
        t.insert("abc");
        t.insert("xyz");

        let results = t.find("q");
        assert!(results.is_empty());
    }
}
