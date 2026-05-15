/// Trie: prefix tree for string storage and search.
/// Teaches: recursive structs with HashMap<char, Box<Node>>,
/// String building during traversal, recursive collect pattern.
///
/// TODO: insert adds chars one-by-one. find collects all words with prefix.
/// delete unmarks is_end and cleans up empty nodes.

use std::collections::HashMap;

struct TrieNode {
    children: HashMap<char, Box<TrieNode>>,
    is_end: bool,
}

impl TrieNode {
    fn new() -> Self {
        TrieNode { children: HashMap::new(), is_end: false }
    }
}

pub struct Trie {
    root: TrieNode,
}

impl Trie {
    pub fn new() -> Self {
        Trie { root: TrieNode::new() }
    }

    pub fn insert(&mut self, word: &str) {
        // TODO: walk/create nodes for each character, mark last as is_end
        // Hint: entry().or_insert_with(|| Box::new(TrieNode::new()))
        todo!()
    }

    pub fn delete(&mut self, word: &str) {
        // TODO: recursively unmark is_end, clean up empty nodes
        let chars: Vec<char> = word.chars().collect();
        Self::delete_helper(&mut self.root, &chars, 0);
    }

    fn delete_helper(node: &mut TrieNode, chars: &[char], depth: usize) -> bool {
        // TODO: implement recursive deletion
        // Return true if parent should remove this child node
        todo!()
    }

    pub fn find(&self, prefix: &str) -> Vec<String> {
        // TODO: walk to prefix node, then collect all words from there
        // Hint: recursive collect with a String buffer
        todo!()
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
