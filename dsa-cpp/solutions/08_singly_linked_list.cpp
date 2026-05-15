#include <cassert>
#include <iostream>
#include <optional>

template <typename T>
class SinglyLinkedList {
public:
    SinglyLinkedList() = default;

    ~SinglyLinkedList() {
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
        head_ = node;
        if (tail_ == nullptr) {
            tail_ = node;
        }
        ++length_;
    }

    void append(const T& value) {
        Node* node = new Node(value);
        if (tail_ == nullptr) {
            head_ = node;
            tail_ = node;
        } else {
            tail_->next = node;
            tail_ = node;
        }
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

        Node* previous = get_node(index - 1);
        Node* node = new Node(value);
        node->next = previous->next;
        previous->next = node;
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
        if (index >= length_) {
            return std::nullopt;
        }

        Node* removed = nullptr;
        if (index == 0) {
            removed = head_;
            head_ = head_->next;
            if (head_ == nullptr) {
                tail_ = nullptr;
            }
        } else {
            Node* previous = get_node(index - 1);
            removed = previous->next;
            previous->next = removed->next;
            if (removed == tail_) {
                tail_ = previous;
            }
        }

        const T value = removed->value;
        delete removed;
        --length_;
        return value;
    }

    bool remove_value(const T& value) {
        Node* current = head_;
        Node* previous = nullptr;

        while (current != nullptr) {
            if (current->value == value) {
                if (previous == nullptr) {
                    head_ = current->next;
                } else {
                    previous->next = current->next;
                }
                if (current == tail_) {
                    tail_ = previous;
                }
                delete current;
                --length_;
                return true;
            }
            previous = current;
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
        Node* next = nullptr;
    };

    Node* get_node(std::size_t index) const {
        if (index >= length_) {
            return nullptr;
        }
        Node* current = head_;
        for (std::size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current;
    }

    Node* head_ = nullptr;
    Node* tail_ = nullptr;
    std::size_t length_ = 0;
};

int main() {
    SinglyLinkedList<int> list;

    list.append(2);
    list.prepend(1);
    list.append(4);
    assert(list.insert_at(2, 3));

    assert(list.length() == 4);
    assert(list.get(0).value() == 1);
    assert(list.get(2).value() == 3);
    assert(list.remove_at(1).value() == 2);
    assert(list.remove_value(4));
    assert(!list.remove_value(42));
    assert(list.length() == 2);
    assert(list.get(1).value() == 3);

    std::cout << "08_singly_linked_list passed\n";
    return 0;
}
