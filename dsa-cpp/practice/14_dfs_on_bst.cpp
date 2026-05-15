// Practice: depth-first search on a binary search tree.
// Teaches recursion, BST ordering, and pointer-based tree traversal.
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

bool dfs(const BinaryNode<int>* node, int needle) {
    // TODO: implement
    // Hint: compare against node->value and recurse only into the side that can contain needle.
    (void)node;
    (void)needle;
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

    assert(dfs(tree.get(), 29));
    assert(dfs(tree.get(), 100));
    assert(!dfs(tree.get(), 13));

    std::cout << "14_dfs_on_bst passed\n";
    return 0;
}
