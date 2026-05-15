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

bool compare(const BinaryNode<int>* left, const BinaryNode<int>* right) {
    if (left == nullptr || right == nullptr) {
        return left == right;
    }
    if (left->value != right->value) {
        return false;
    }
    return compare(left->left.get(), right->left.get()) &&
           compare(left->right.get(), right->right.get());
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
    const auto tree_a = build_tree();
    const auto tree_b = build_tree();
    auto tree_c = build_tree();
    tree_c->right->left->right->value = 46;

    assert(compare(tree_a.get(), tree_b.get()));
    assert(!compare(tree_a.get(), tree_c.get()));
    assert(compare(nullptr, nullptr));

    std::cout << "13_compare_binary_trees passed\n";
    return 0;
}
