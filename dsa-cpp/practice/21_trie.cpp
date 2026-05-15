// Practice: trie for prefix search and deletion.
// Teaches arrays of std::unique_ptr, recursion, and string prefix operations.
#include <array>
#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Trie {
public:
    void insert(const std::string& word) {
        // TODO: implement
        // Hint: walk/create child nodes for each character, then mark the final node as a word.
        (void)word;
    }

    void delete_word(const std::string& word) {
        // TODO: implement
        // Hint: recurse down the word, clear is_word, and prune unused children on the way back.
        (void)word;
    }

    std::vector<std::string> find(const std::string& prefix) const {
        // TODO: implement
        // Hint: walk to the prefix node, then collect all words beneath it.
        (void)prefix;
        return {};
    }

private:
    struct Node {
        std::array<std::unique_ptr<Node>, 26> children{};
        bool is_word = false;
    };

    static std::size_t to_index(char ch) {
        // TODO: implement
        // Hint: map lowercase letters so 'a' becomes 0.
        (void)ch;
        return 0;
    }

    static bool has_children(const Node* node) {
        // TODO: implement
        // Hint: return true if any child pointer is non-null.
        (void)node;
        return false;
    }

    static bool erase(Node* node, const std::string& word, std::size_t depth) {
        // TODO: implement
        // Hint: recurse to the end of the word, unset is_word, then tell the caller whether this node can be deleted.
        (void)node;
        (void)word;
        (void)depth;
        return false;
    }

    static void collect(const Node* node, const std::string& prefix, std::vector<std::string>& out) {
        // TODO: implement
        // Hint: add prefix when node->is_word is true, then recurse through existing children.
        (void)node;
        (void)prefix;
        (void)out;
    }

    Node root_;
};

int main() {
    Trie trie;
    trie.insert("cat");
    trie.insert("car");
    trie.insert("cap");
    trie.insert("dog");

    const std::vector<std::string> expected_before{"cap", "car", "cat"};
    assert(trie.find("ca") == expected_before);

    trie.delete_word("car");
    const std::vector<std::string> expected_after{"cap", "cat"};
    assert(trie.find("ca") == expected_after);
    assert(trie.find("do") == std::vector<std::string>{"dog"});
    assert(trie.find("z").empty());

    std::cout << "21_trie passed\n";
    return 0;
}
