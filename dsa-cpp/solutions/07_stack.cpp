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
        auto node = std::make_unique<Node>(std::move(value));
        node->next = std::move(head_);
        head_ = std::move(node);
        ++length_;
    }

    std::optional<T> pop() {
        if (!head_) {
            return std::nullopt;
        }

        T value = std::move(head_->value);
        head_ = std::move(head_->next);
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
