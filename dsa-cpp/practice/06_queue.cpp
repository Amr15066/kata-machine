// Practice: queue backed by a linked list.
// Teaches templates, std::unique_ptr ownership, and FIFO operations.
#include <cassert>
#include <iostream>
#include <memory>
#include <optional>
#include <string>

template <typename T>
class Queue {
public:
    Queue() = default;

    void enqueue(T value) {
        // TODO: implement
        // Hint: append a new node at tail_ and update head_ when the queue is empty.
        (void)value;
    }

    std::optional<T> dequeue() {
        // TODO: implement
        // Hint: remove from head_, update tail_ when the queue becomes empty, and decrement length_.
        return std::nullopt;
    }

    std::optional<T> peek() const {
        // TODO: implement
        // Hint: return the head value without removing it.
        return std::nullopt;
    }

    std::size_t length() const {
        // TODO: implement
        // Hint: return the tracked queue length.
        return length_;
    }

private:
    struct Node {
        explicit Node(T value_in) : value(std::move(value_in)) {}

        T value;
        std::unique_ptr<Node> next;
    };

    std::unique_ptr<Node> head_;
    Node* tail_ = nullptr;  // Non-owning pointer for O(1) enqueue.
    std::size_t length_ = 0;
};

int main() {
    Queue<std::string> queue;

    assert(queue.length() == 0);
    assert(!queue.peek().has_value());
    queue.enqueue("first");
    queue.enqueue("second");
    queue.enqueue("third");

    assert(queue.length() == 3);
    assert(queue.peek().value() == "first");
    assert(queue.dequeue().value() == "first");
    assert(queue.dequeue().value() == "second");
    assert(queue.dequeue().value() == "third");
    assert(!queue.dequeue().has_value());
    assert(queue.length() == 0);

    std::cout << "06_queue passed\n";
    return 0;
}
