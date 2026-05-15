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
        auto node = std::make_unique<Node>(std::move(value));
        Node* new_tail = node.get();

        if (!head_) {
            head_ = std::move(node);
            tail_ = new_tail;
        } else {
            tail_->next = std::move(node);
            tail_ = new_tail;
        }

        ++length_;
    }

    std::optional<T> dequeue() {
        if (!head_) {
            return std::nullopt;
        }

        T value = std::move(head_->value);
        head_ = std::move(head_->next);
        if (!head_) {
            tail_ = nullptr;
        }
        --length_;
        return value;
    }

    std::optional<T> peek() const {
        if (!head_) {
            return std::nullopt;
        }
        return head_->value;
    }

    std::size_t length() const {
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
