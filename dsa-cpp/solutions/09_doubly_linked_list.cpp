#include <cassert>
#include <iostream>
#include <optional>

template <typename T>
class DoublyLinkedList {
public:
    DoublyLinkedList() = default;

    ~DoublyLinkedList() {
        Node* current = head_;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    void prepend(const T& value) {
        Node* node = new Node(value);
        node->next = head_;
        if (head_ != nullptr) {
            head_->prev = node;
        }
        head_ = node;
        if (tail_ == nullptr) {
            tail_ = node;
        }
        ++length_;
    }

    void append(const T& value) {
        Node* node = new Node(value);
        node->prev = tail_;
        if (tail_ != nullptr) {
            tail_->next = node;
        } else {
            head_ = node;
        }
        tail_ = node;
        ++length_;
    }

    bool insert_at(std::size_t index, const T& value) {
        if (index > length_) {
            return false;
        }
        if (index == 0) {
            prepend(value);
            return true;
        }
        if (index == length_) {
            append(value);
            return true;
        }

        Node* next = get_node(index);
        Node* previous = next->prev;
        Node* node = new Node(value);
        node->prev = previous;
        node->next = next;
        previous->next = node;
        next->prev = node;
        ++length_;
        return true;
    }

    std::optional<T> get(std::size_t index) const {
        Node* node = get_node(index);
        if (node == nullptr) {
            return std::nullopt;
        }
        return node->value;
    }

    std::optional<T> remove_at(std::size_t index) {
        Node* node = get_node(index);
        if (node == nullptr) {
            return std::nullopt;
        }

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

        const T value = node->value;
        delete node;
        --length_;
        return value;
    }

    bool remove_value(const T& value) {
        Node* current = head_;
        while (current != nullptr) {
            if (current->value == value) {
                if (current->prev != nullptr) {
                    current->prev->next = current->next;
                } else {
                    head_ = current->next;
                }
                if (current->next != nullptr) {
                    current->next->prev = current->prev;
                } else {
                    tail_ = current->prev;
                }
                delete current;
                --length_;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    std::size_t length() const {
        return length_;
    }

private:
    struct Node {
        explicit Node(const T& value_in) : value(value_in) {}

        T value;
        Node* prev = nullptr;
        Node* next = nullptr;
    };

    Node* get_node(std::size_t index) const {
        if (index >= length_) {
            return nullptr;
        }
        Node* current = nullptr;
        if (index < length_ / 2) {
            current = head_;
            for (std::size_t i = 0; i < index; ++i) {
                current = current->next;
            }
        } else {
            current = tail_;
            for (std::size_t i = length_ - 1; i > index; --i) {
                current = current->prev;
            }
        }
        return current;
    }

    Node* head_ = nullptr;
    Node* tail_ = nullptr;
    std::size_t length_ = 0;
};

int main() {
    DoublyLinkedList<int> list;

    list.append(2);
    list.prepend(1);
    list.append(4);
    assert(list.insert_at(2, 3));

    assert(list.length() == 4);
    assert(list.get(3).value() == 4);
    assert(list.remove_at(2).value() == 3);
    assert(list.remove_value(4));
    assert(!list.remove_value(99));
    assert(list.length() == 2);
    assert(list.get(1).value() == 2);

    std::cout << "09_doubly_linked_list passed\n";
    return 0;
}
