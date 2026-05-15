// Practice: stack backed by a linked list.
// Teaches templates, std::unique_ptr ownership, and LIFO operations.
#include <cassert>
#include <iostream>
#include <memory>
#include <optional>
#include <string>

template <typename T>
class Stack {
public:
    Stack() = default;

    void push(T value) {
        // TODO: implement
        // Hint: add the new node at the front and increment length_.
        (void)value;
    }

    std::optional<T> pop() {
        // TODO: implement
        // Hint: remove the head node, move its value out, and decrement length_.
        return std::nullopt;
    }

    std::optional<T> peek() const {
        // TODO: implement
        // Hint: return the current head value without changing the stack.
        return std::nullopt;
    }

    std::size_t length() const {
        // TODO: implement
        // Hint: return the tracked stack length.
        return length_;
    }

private:
    struct Node {
        explicit Node(T value_in) : value(std::move(value_in)) {}

        T value;
        std::unique_ptr<Node> next;
    };

    std::unique_ptr<Node> head_;
    std::size_t length_ = 0;
};

int main() {
    Stack<std::string> stack;

    assert(stack.length() == 0);
    stack.push("first");
    stack.push("second");
    stack.push("third");

    assert(stack.length() == 3);
    assert(stack.peek().value() == "third");
    assert(stack.pop().value() == "third");
    assert(stack.pop().value() == "second");
    assert(stack.pop().value() == "first");
    assert(!stack.pop().has_value());

    std::cout << "07_stack passed\n";
    return 0;
}
