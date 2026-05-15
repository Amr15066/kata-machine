// Practice: least-recently-used cache.
// Teaches templates, doubly linked lists, hash-table lookup, and eviction.
#include <cassert>
#include <iostream>
#include <optional>
#include <string>
#include <unordered_map>

template <typename V>
class LRUCache {
public:
    explicit LRUCache(std::size_t capacity) : capacity_(capacity) {
        assert(capacity_ > 0);
    }

    ~LRUCache() {
        Node* current = head_;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    void update(const std::string& key, const V& value) {
        // TODO: implement
        // Hint: update-and-move existing nodes, or insert a new front node and evict tail_ when over capacity.
        (void)key;
        (void)value;
    }

    std::optional<V> get(const std::string& key) {
        // TODO: implement
        // Hint: look up the node, move it to the front on a hit, and return std::nullopt on a miss.
        (void)key;
        return std::nullopt;
    }

private:
    struct Node {
        Node(const std::string& key_in, const V& value_in) : key(key_in), value(value_in) {}

        std::string key;
        V value;
        Node* prev = nullptr;
        Node* next = nullptr;
    };

    void add_to_front(Node* node) {
        // TODO: implement
        // Hint: link node before head_ and update tail_ if the list was empty.
        (void)node;
    }

    void detach(Node* node) {
        // TODO: implement
        // Hint: unlink node from its neighbors and repair head_/tail_.
        (void)node;
    }

    void move_to_front(Node* node) {
        // TODO: implement
        // Hint: skip work when node is already head_, otherwise detach then re-add.
        (void)node;
    }

    std::size_t capacity_;
    std::unordered_map<std::string, Node*> lookup_;  // Map holds non-owning pointers.
    Node* head_ = nullptr;
    Node* tail_ = nullptr;
};

int main() {
    LRUCache<int> cache(2);

    cache.update("a", 1);
    cache.update("b", 2);
    assert(cache.get("a").value() == 1);

    cache.update("c", 3);  // Evicts "b" because "a" was just used.
    assert(!cache.get("b").has_value());
    assert(cache.get("c").value() == 3);

    cache.update("a", 10);
    assert(cache.get("a").value() == 10);

    std::cout << "20_lru_cache passed\n";
    return 0;
}
