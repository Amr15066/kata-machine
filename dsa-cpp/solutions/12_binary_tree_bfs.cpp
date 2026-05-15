#include <cassert>
#include <iostream>
#include <memory>

template <typename T>
struct BinaryNode {
    explicit BinaryNode(T value_in) : value(value_in) {}

    T value;
    std::unique_ptr<BinaryNode<T>> left;
    std::unique_ptr<BinaryNode<T>> right;
};

class NodeQueue {
public:
    ~NodeQueue() {
        while (head_ != nullptr) {
            Entry* next = head_->next;
            delete head_;
            head_ = next;
        }
    }

    void push(BinaryNode<int>* value) {
        Entry* entry = new Entry(value);
        if (tail_ == nullptr) {
            head_ = entry;
            tail_ = entry;
        } else {
            tail_->next = entry;
            tail_ = entry;
        }
    }

    BinaryNode<int>* pop() {
        assert(head_ != nullptr);
        Entry* entry = head_;
        BinaryNode<int>* value = entry->value;
        head_ = head_->next;
        if (head_ == nullptr) {
            tail_ = nullptr;
        }
        delete entry;
        return value;
    }

    bool empty() const {
        return head_ == nullptr;
    }

private:
    struct Entry {
        explicit Entry(BinaryNode<int>* value_in) : value(value_in) {}

        BinaryNode<int>* value;
        Entry* next = nullptr;
    };

    Entry* head_ = nullptr;
    Entry* tail_ = nullptr;
};

bool bfs(BinaryNode<int>* root, int needle) {
    if (root == nullptr) {
        return false;
    }

    NodeQueue queue;
    queue.push(root);

    while (!queue.empty()) {
        BinaryNode<int>* current = queue.pop();
        if (current->value == needle) {
            return true;
        }
        if (current->left) {
            queue.push(current->left.get());
        }
        if (current->right) {
            queue.push(current->right.get());
        }
    }

    return false;
}

std::unique_ptr<BinaryNode<int>> build_tree() {
    auto root = std::make_unique<BinaryNode<int>>(20);
    root->left = std::make_unique<BinaryNode<int>>(10);
    root->right = std::make_unique<BinaryNode<int>>(50);
    root->left->left = std::make_unique<BinaryNode<int>>(5);
    root->left->right = std::make_unique<BinaryNode<int>>(15);
    root->left->left->right = std::make_unique<BinaryNode<int>>(7);
    root->right->left = std::make_unique<BinaryNode<int>>(30);
    root->right->right = std::make_unique<BinaryNode<int>>(100);
    root->right->left->left = std::make_unique<BinaryNode<int>>(29);
    root->right->left->right = std::make_unique<BinaryNode<int>>(45);
    return root;
}

int main() {
    const auto tree = build_tree();

    assert(bfs(tree.get(), 45));
    assert(bfs(tree.get(), 7));
    assert(!bfs(tree.get(), 999));

    std::cout << "12_binary_tree_bfs passed\n";
    return 0;
}
