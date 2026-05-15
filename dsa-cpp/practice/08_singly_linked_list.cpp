// Practice: singly linked list operations.
// Teaches templates, pointer manipulation, and basic list mutation.
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
        // TODO: implement
        // Hint: insert at the head, update tail_ when the list was empty, and increment length_.
        (void)value;
    }

    void append(const T& value) {
        // TODO: implement
        // Hint: attach a new node after tail_ or initialize both head_ and tail_.
        (void)value;
    }

    bool insert_at(std::size_t index, const T& value) {
        // TODO: implement
        // Hint: handle index 0 and length_ as special cases, otherwise splice into the middle.
        (void)index;
        (void)value;
        return false;
    }

    std::optional<T> get(std::size_t index) const {
        // TODO: implement
        // Hint: walk to the node at index and return its value if it exists.
        (void)index;
        return std::nullopt;
    }

    std::optional<T> remove_at(std::size_t index) {
        // TODO: implement
        // Hint: unlink the node at index, fix head_/tail_, and decrement length_.
        (void)index;
        return std::nullopt;
    }

    bool remove_value(const T& value) {
        // TODO: implement
        // Hint: find the first matching node, unlink it, and update tail_ if needed.
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
        Node* next = nullptr;
    };

    Node* get_node(std::size_t index) const {
        // TODO: implement
        // Hint: walk from head_ index steps, or return nullptr when out of bounds.
        (void)index;
        return nullptr;
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
