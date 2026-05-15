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
        auto found = lookup_.find(key);
        if (found != lookup_.end()) {
            found->second->value = value;
            move_to_front(found->second);
            return;
        }

        Node* node = new Node(key, value);
        lookup_[key] = node;
        add_to_front(node);

        if (lookup_.size() > capacity_) {
            Node* victim = tail_;
            detach(victim);
            lookup_.erase(victim->key);
            delete victim;
        }
    }

    std::optional<V> get(const std::string& key) {
        auto found = lookup_.find(key);
        if (found == lookup_.end()) {
            return std::nullopt;
        }
        move_to_front(found->second);
        return found->second->value;
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
        node->prev = nullptr;
        node->next = head_;
        if (head_ != nullptr) {
            head_->prev = node;
        }
        head_ = node;
        if (tail_ == nullptr) {
            tail_ = node;
        }
    }

    void detach(Node* node) {
        if (node->prev != nullptr) {
            node->prev->next = node->next;
        } else {
            head_ = node->next;
        }
        if (node->next != nullptr) {
            node->next->prev = node->prev;
        } else {
            tail_ = node->prev;
        }
        node->prev = nullptr;
        node->next = nullptr;
    }

    void move_to_front(Node* node) {
        if (node == head_) {
            return;
        }
        detach(node);
        add_to_front(node);
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
