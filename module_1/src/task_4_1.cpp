#include "../include/Heap.hpp"
#include "../include/Pair.hpp"
#include <cstddef>
#include <iostream>

template <typename T>
struct Descriptor {
    T *_array;
    size_t _index;

    Descriptor() : _array(nullptr), _index(0) {}

    explicit Descriptor(T *array) {
        _array = array;
        _index = 0;
    }

    ~Descriptor() {
        _array = nullptr;
    }

    [[nodiscard]] constexpr T &operator[](int idx) const {
        assert(idx >= 0 && idx < _index && _array != nullptr);
        return &_array[idx];
    }

    bool operator==(const Descriptor<T> &other) { return _array[_index] == other._array[other._index]; }

    bool operator!=(const Descriptor<T> &other) { return _array[_index] != other._array[other._index]; }

    bool operator<(const Descriptor<T> &other) const { return _array[_index] < other._array[other._index]; }

    bool operator>(const Descriptor<T> &other) const { return _array[_index] > other._array[other._index]; }

    bool operator<=(const Descriptor<T> &other) const { return _array[_index] <= other._array[other._index]; }

    bool operator>=(const Descriptor<T> &other) const { return _array[_index] >= other._array[other._index]; }
};

bool operator<(const Pair<Descriptor<int>, int> &lhs, const Pair<Descriptor<int>, int> &rhs) {
    return lhs._first < rhs._first;
}

bool operator>(const Pair<Descriptor<int>, int> &lhs, const Pair<Descriptor<int>, int> &rhs) {
    return lhs._first > rhs._first;
}

bool operator<=(const Pair<Descriptor<int>, int> &lhs, const Pair<Descriptor<int>, int> &rhs) {
    return lhs._first <= rhs._first;
}

bool operator>=(const Pair<Descriptor<int>, int> &lhs, const Pair<Descriptor<int>, int> &rhs) {
    return lhs._first >= rhs._first;
}

Heap<Pair<Descriptor<int>, int>> parseHeapFromIO(std::istream &input_stream) {
    int array_count, array_size, element;
    Heap<Pair<Descriptor<int>, int>> resulting_heap;
    input_stream >> array_count;
    for (int i = 0; i < array_count; ++i) {
        input_stream >> array_size;
        int *temp_array = new int[array_size];
        for (int j = 0; j < array_size; ++j) {
            input_stream >> element;
            temp_array[j] = element;
        }
        Descriptor<int> descriptor(temp_array);
        Pair<Descriptor<int>, int> logical_pair(descriptor, array_size);
        resulting_heap.push(logical_pair);
    }
    return resulting_heap;
}

void solve(Heap<Pair<Descriptor<int>, int>> &heap, std::ostream &stream) {
    while (!heap.isEmpty()) {
        Pair<Descriptor<int>, int> smallest = heap.top();
        heap.pop();

        stream << smallest._first._array[smallest._first._index] << ' ';

        if (smallest._first._index + 1 < smallest._second) {
            smallest._first._index++;
            heap.push(smallest);
        } else {
            delete smallest._first._array;
        }
    }
}

namespace task_4_1 {
    void IO(std::istream &input_stream, std::ostream &output_stream) {
        Heap<Pair<Descriptor<int>, int>> heap = parseHeapFromIO(input_stream);
        solve(heap, output_stream);
    }
}