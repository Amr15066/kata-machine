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
        Node* current = buckets_[index_for(key)];
        while (current != nullptr) {
            if (current->key == key) {
                current->value = value;
                return;
            }
            current = current->next;
        }

        const std::size_t index = index_for(key);
        Node* node = new Node(key, value);
        node->next = buckets_[index];
        buckets_[index] = node;
        ++size_;
    }

    std::optional<V> get(const std::string& key) const {
        Node* current = buckets_[index_for(key)];
        while (current != nullptr) {
            if (current->key == key) {
                return current->value;
            }
            current = current->next;
        }
        return std::nullopt;
    }

    bool remove(const std::string& key) {
        const std::size_t index = index_for(key);
        Node* current = buckets_[index];
        Node* previous = nullptr;

        while (current != nullptr) {
            if (current->key == key) {
                if (previous == nullptr) {
                    buckets_[index] = current->next;
                } else {
                    previous->next = current->next;
                }
                delete current;
                --size_;
                return true;
            }
            previous = current;
            current = current->next;
        }

        return false;
    }

    std::size_t size() const {
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
        unsigned long long hash = 5381;
        for (char ch : key) {
            hash = ((hash << 5U) + hash) + static_cast<unsigned long long>(ch);
        }
        return static_cast<std::size_t>(hash % buckets_.size());
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
