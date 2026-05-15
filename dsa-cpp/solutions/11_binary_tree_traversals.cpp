#include <cassert>
#include <iostream>
#include <memory>
#include <vector>

template <typename T>
struct BinaryNode {
    explicit BinaryNode(T value_in) : value(value_in) {}

    T value;
    std::unique_ptr<BinaryNode<T>> left;
    std::unique_ptr<BinaryNode<T>> right;
};

template <typename T>
void pre_order_impl(const BinaryNode<T>* node, std::vector<T>& out) {
    if (node == nullptr) {
        return;
    }
    out.push_back(node->value);
    pre_order_impl(node->left.get(), out);
    pre_order_impl(node->right.get(), out);
}

template <typename T>
void in_order_impl(const BinaryNode<T>* node, std::vector<T>& out) {
    if (node == nullptr) {
        return;
    }
    in_order_impl(node->left.get(), out);
    out.push_back(node->value);
    in_order_impl(node->right.get(), out);
}

template <typename T>
void post_order_impl(const BinaryNode<T>* node, std::vector<T>& out) {
    if (node == nullptr) {
        return;
    }
    post_order_impl(node->left.get(), out);
    post_order_impl(node->right.get(), out);
    out.push_back(node->value);
}

template <typename T>
std::vector<T> pre_order(const BinaryNode<T>* node) {
    std::vector<T> out;
    pre_order_impl(node, out);
    return out;
}

template <typename T>
std::vector<T> in_order(const BinaryNode<T>* node) {
    std::vector<T> out;
    in_order_impl(node, out);
    return out;
}

template <typename T>
std::vector<T> post_order(const BinaryNode<T>* node) {
    std::vector<T> out;
    post_order_impl(node, out);
    return out;
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

    const std::vector<int> expected_pre{20, 10, 5, 7, 15, 50, 30, 29, 45, 100};
    const std::vector<int> expected_in{5, 7, 10, 15, 20, 29, 30, 45, 50, 100};
    const std::vector<int> expected_post{7, 5, 15, 10, 29, 45, 30, 100, 50, 20};

    assert(pre_order(tree.get()) == expected_pre);
    assert(in_order(tree.get()) == expected_in);
    assert(post_order(tree.get()) == expected_post);

    std::cout << "11_binary_tree_traversals passed\n";
    return 0;
}
