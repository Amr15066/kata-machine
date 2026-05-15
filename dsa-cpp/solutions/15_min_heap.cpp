#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

class MinHeap {
public:
    void insert(int value) {
        data_.push_back(value);
        heapify_up(data_.size() - 1);
    }

    int delete_min() {
        assert(!data_.empty());
        const int value = data_.front();
        data_.front() = data_.back();
        data_.pop_back();
        if (!data_.empty()) {
            heapify_down(0);
        }
        return value;
    }

    std::size_t length() const {
        return data_.size();
    }

private:
    void heapify_up(std::size_t index) {
        while (index > 0) {
            const std::size_t parent = (index - 1) / 2;
            if (data_[parent] <= data_[index]) {
                break;
            }
            std::swap(data_[parent], data_[index]);
            index = parent;
        }
    }

    void heapify_down(std::size_t index) {
        while (true) {
            const std::size_t left = index * 2 + 1;
            const std::size_t right = index * 2 + 2;
            std::size_t smallest = index;

            if (left < data_.size() && data_[left] < data_[smallest]) {
                smallest = left;
            }
            if (right < data_.size() && data_[right] < data_[smallest]) {
                smallest = right;
            }
            if (smallest == index) {
                break;
            }

            std::swap(data_[index], data_[smallest]);
            index = smallest;
        }
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
