// Practice: binary min-heap operations.
// Teaches array-backed trees, heap invariants, and index arithmetic.
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

class MinHeap {
public:
    void insert(int value) {
        // TODO: implement
        // Hint: push the value at the end, then bubble it up until the heap property holds.
        (void)value;
    }

    int delete_min() {
        // TODO: implement
        // Hint: remove the root, move the last element to index 0, then heapify down.
        return 0;
    }

    std::size_t length() const {
        // TODO: implement
        // Hint: return the number of stored heap elements.
        return data_.size();
    }

private:
    void heapify_up(std::size_t index) {
        // TODO: implement
        // Hint: compare the node with its parent and swap while it is smaller.
        (void)index;
    }

    void heapify_down(std::size_t index) {
        // TODO: implement
        // Hint: swap with the smaller child until the heap property is restored.
        (void)index;
    }

    std::vector<int> data_;
};

int main() {
    MinHeap heap;

    heap.insert(5);
    heap.insert(3);
    heap.insert(8);
    heap.insert(1);
    heap.insert(6);

    assert(heap.length() == 5);
    assert(heap.delete_min() == 1);
    assert(heap.delete_min() == 3);
    assert(heap.delete_min() == 5);
    assert(heap.delete_min() == 6);
    assert(heap.delete_min() == 8);
    assert(heap.length() == 0);

    std::cout << "15_min_heap passed\n";
    return 0;
}
