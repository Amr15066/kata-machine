// Practice: doubly linked list operations.
// Teaches templates, bidirectional pointers, and indexed list updates.
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
        // TODO: implement
        // Hint: link the new node before head_ and update tail_ when inserting into an empty list.
        (void)value;
    }

    void append(const T& value) {
        // TODO: implement
        // Hint: link the new node after tail_ or initialize head_ and tail_.
        (void)value;
    }

    bool insert_at(std::size_t index, const T& value) {
        // TODO: implement
        // Hint: handle ends specially, otherwise splice between previous and next nodes.
        (void)index;
        (void)value;
        return false;
    }

    std::optional<T> get(std::size_t index) const {
        // TODO: implement
        // Hint: reuse get_node and return the node value when found.
        (void)index;
        return std::nullopt;
    }

    std::optional<T> remove_at(std::size_t index) {
        // TODO: implement
        // Hint: unlink the node, fix neighboring prev/next pointers, and decrement length_.
        (void)index;
        return std::nullopt;
    }

    bool remove_value(const T& value) {
        // TODO: implement
        // Hint: search for the first matching node and unlink it from both sides.
        (void)value;
        return false;
    }

    std::size_t length() const {
        // TODO: implement
        // Hint: return the tracked list length.
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
        // TODO: implement
        // Hint: walk from the closer end: head_ for early indexes, tail_ for late indexes.
        (void)index;
        return nullptr;
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
