#pragma once
#include "DynamicArray.hpp"

template <typename T>
struct DefaultComparator {
    bool operator()(const T &left, const T &right) const {
        return left > right;
    }
};

template <typename T, typename Comparator = DefaultComparator<T>>
class Heap {
private:
    DynamicArray<T> _array;
    Comparator _comparator;

    void siftUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (_comparator(_array[index], _array[parent]))
                return;
            std::swap(_array[index], _array[parent]);
            index = parent;
        }
    }

    void siftDown(int index) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int actual = index;
        if (left < _array.getSize() && !_comparator(_array[left], _array[index]))
            actual = left;
        if (right < _array.getSize() && !_comparator(_array[right], _array[actual]))
            actual = right;
        if (actual != index) {
            std::swap(_array[index], _array[actual]);
            siftDown(actual);
        }
    }

public:
    explicit Heap(Comparator comparator = Comparator()) {
        _comparator = comparator;
    }

    Heap(size_t size, Comparator comparator = Comparator()) {
        _comparator = comparator;
        _array.reserve(size);
    }

    explicit Heap(const DynamicArray<T> &array, Comparator comparator = Comparator()) {
        _array = array;
        _comparator = comparator;
        for (int i = this->_array.getSize() / 2 - 1; i >= 0; --i)
            siftDown(i);
    }

    Heap(const Heap &other) {
        this->_comparator = other._comparator;
        this->_array = other._array;
    }

    Heap(Heap &&other) noexcept {
        _array = std::move(other._array);
        _comparator = std::move(other._comparator);
    }

    ~Heap() {
        _array.clear();
    }

    Heap &operator=(const Heap &other) {
        if (this != &other) {
            this->_array = other._array;
            this->_comparator = other._comparator;
        }
        return *this;
    }

    Heap &operator=(Heap &&heap) = delete;

    [[nodiscard]] const T &top() const {
        return _array[0];
    }

    void push(const T &element) {
        _array.push_back(element);
        siftUp(_array.getSize() - 1);
    }

    void pop() {
        if (!_array.isEmpty()) {
            std::swap(_array[0], _array[_array.getSize() - 1]);
            _array.pop_back();
            if (!_array.isEmpty()) {
                siftDown(0);
            }
        }
    }

    bool isEmpty() {
        return _array.isEmpty();
    }
};