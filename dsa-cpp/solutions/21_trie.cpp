#include <array>
#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Trie {
public:
    void insert(const std::string& word) {
        Node* current = &root_;
        for (char ch : word) {
            const std::size_t index = to_index(ch);
            if (!current->children[index]) {
                current->children[index] = std::make_unique<Node>();
            }
            current = current->children[index].get();
        }
        current->is_word = true;
    }

    void delete_word(const std::string& word) {
        erase(&root_, word, 0);
    }

    std::vector<std::string> find(const std::string& prefix) const {
        const Node* current = &root_;
        for (char ch : prefix) {
            const std::size_t index = to_index(ch);
            if (!current->children[index]) {
                return {};
            }
            current = current->children[index].get();
        }

        std::vector<std::string> out;
        collect(current, prefix, out);
        return out;
    }

private:
    struct Node {
        std::array<std::unique_ptr<Node>, 26> children{};
        bool is_word = false;
    };

    static std::size_t to_index(char ch) {
        return static_cast<std::size_t>(ch - 'a');
    }

    static bool has_children(const Node* node) {
        for (const auto& child : node->children) {
            if (child) {
                return true;
            }
        }
        return false;
    }

    static bool erase(Node* node, const std::string& word, std::size_t depth) {
        if (depth == word.size()) {
            if (!node->is_word) {
                return false;
            }
            node->is_word = false;
            return !has_children(node);
        }

        const std::size_t index = to_index(word[depth]);
        if (!node->children[index]) {
            return false;
        }

        if (erase(node->children[index].get(), word, depth + 1)) {
            node->children[index].reset();
        }

        return !node->is_word && !has_children(node);
    }

    static void collect(const Node* node, const std::string& prefix, std::vector<std::string>& out) {
        if (node->is_word) {
            out.push_back(prefix);
        }

        for (std::size_t i = 0; i < node->children.size(); ++i) {
            if (node->children[i]) {
                const char next = static_cast<char>('a' + i);
                collect(node->children[i].get(), prefix + next, out);
            }
        }
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
