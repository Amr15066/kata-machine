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
        insert_at(0, value);
    }

    void append(const T& value) {
        ensure_capacity(length_ + 1);
        data_[length_] = value;
        ++length_;
    }

    bool insert_at(std::size_t index, const T& value) {
        if (index > length_) {
            return false;
        }
        ensure_capacity(length_ + 1);
        for (std::size_t i = length_; i > index; --i) {
            data_[i] = data_[i - 1];
        }
        data_[index] = value;
        ++length_;
        return true;
    }

    std::optional<T> get(std::size_t index) const {
        if (index >= length_) {
            return std::nullopt;
        }
        return data_[index];
    }

    std::optional<T> remove_at(std::size_t index) {
        if (index >= length_) {
            return std::nullopt;
        }

        const T value = data_[index];
        for (std::size_t i = index; i + 1 < length_; ++i) {
            data_[i] = data_[i + 1];
        }
        --length_;
        return value;
    }

    bool remove_value(const T& value) {
        for (std::size_t i = 0; i < length_; ++i) {
            if (data_[i] == value) {
                remove_at(i);
                return true;
            }
        }
        return false;
    }

    std::size_t length() const {
        return length_;
    }

private:
    void ensure_capacity(std::size_t needed) {
        if (needed <= capacity_) {
            return;
        }

        std::size_t new_capacity = capacity_;
        while (new_capacity < needed) {
            new_capacity *= 2;
        }

        T* new_data = new T[new_capacity];
        std::copy(data_, data_ + length_, new_data);
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
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
