// Practice: hash map with separate chaining.
// Teaches templates, hashing strings, linked buckets, and std::optional lookups.
#include <cassert>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

template <typename V>
class HashMap {
public:
    explicit HashMap(std::size_t bucket_count = 16) : buckets_(bucket_count, nullptr) {}

    ~HashMap() {
        for (Node* bucket : buckets_) {
            while (bucket != nullptr) {
                Node* next = bucket->next;
                delete bucket;
                bucket = next;
            }
        }
    }

    void set(const std::string& key, const V& value) {
        // TODO: implement
        // Hint: update an existing key in-place, otherwise prepend a new node into the selected bucket.
        (void)key;
        (void)value;
    }

    std::optional<V> get(const std::string& key) const {
        // TODO: implement
        // Hint: hash into the bucket, scan the chain, and return std::nullopt when missing.
        (void)key;
        return std::nullopt;
    }

    bool remove(const std::string& key) {
        // TODO: implement
        // Hint: unlink the matching node from its bucket chain and decrement size_.
        (void)key;
        return false;
    }

    std::size_t size() const {
        // TODO: implement
        // Hint: return the number of stored keys.
        return size_;
    }

private:
    struct Node {
        Node(const std::string& key_in, const V& value_in) : key(key_in), value(value_in) {}

        std::string key;
        V value;
        Node* next = nullptr;
    };

    std::size_t index_for(const std::string& key) const {
        // TODO: implement
        // Hint: compute a deterministic hash and mod by buckets_.size().
        (void)key;
        return 0;
    }

    std::vector<Node*> buckets_;
    std::size_t size_ = 0;
};

int main() {
    HashMap<int> map;

    map.set("alice", 10);
    map.set("bob", 20);
    map.set("alice", 15);

    assert(map.size() == 2);
    assert(map.get("alice").value() == 15);
    assert(map.get("bob").value() == 20);
    assert(!map.get("missing").has_value());
    assert(map.remove("bob"));
    assert(!map.remove("bob"));
    assert(map.size() == 1);

    std::cout << "19_hash_map passed\n";
    return 0;
}
