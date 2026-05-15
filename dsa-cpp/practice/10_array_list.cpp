// Practice: dynamic array list with indexed updates.
// Teaches templates, manual memory management, and capacity growth.
#include <algorithm>
#include <cassert>
#include <iostream>
#include <optional>

template <typename T>
class ArrayList {
public:
    ArrayList() : capacity_(4), data_(new T[capacity_]) {}

    ~ArrayList() {
        delete[] data_;
    }

    void prepend(const T& value) {
        // TODO: implement
        // Hint: reuse insert_at with index 0.
        (void)value;
    }

    void append(const T& value) {
        // TODO: implement
        // Hint: ensure capacity, write at data_[length_], then increment length_.
        (void)value;
    }

    bool insert_at(std::size_t index, const T& value) {
        // TODO: implement
        // Hint: shift elements right from the end down to index.
        (void)index;
        (void)value;
        return false;
    }

    std::optional<T> get(std::size_t index) const {
        // TODO: implement
        // Hint: return std::nullopt for out-of-range access.
        (void)index;
        return std::nullopt;
    }

    std::optional<T> remove_at(std::size_t index) {
        // TODO: implement
        // Hint: save the value, shift elements left, and decrement length_.
        (void)index;
        return std::nullopt;
    }

    bool remove_value(const T& value) {
        // TODO: implement
        // Hint: find the first matching element and delegate to remove_at.
        (void)value;
        return false;
    }

    std::size_t length() const {
        // TODO: implement
        // Hint: return the tracked logical length.
        return length_;
    }

private:
    void ensure_capacity(std::size_t needed) {
        // TODO: implement
        // Hint: grow capacity geometrically, copy existing elements, then swap buffers.
        (void)needed;
    }

    std::size_t length_ = 0;
    std::size_t capacity_ = 0;
    T* data_ = nullptr;
};

int main() {
    ArrayList<int> list;

    list.append(2);
    list.prepend(1);
    list.append(4);
    assert(list.insert_at(2, 3));

    assert(list.length() == 4);
    assert(list.get(0).value() == 1);
    assert(list.get(2).value() == 3);
    assert(list.remove_at(1).value() == 2);
    assert(list.remove_value(4));
    assert(!list.remove_value(10));
    assert(list.length() == 2);
    assert(list.get(1).value() == 3);

    std::cout << "10_array_list passed\n";
    return 0;
}
