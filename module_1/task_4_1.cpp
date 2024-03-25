#include <cassert>
#include <algorithm>
#include <iostream>
#include <vector>

#define PRINT_ARRAY_INFO(array) std::cout << "Size: " << array.getSize() << ", Capacity: " << array.getCapacity() << std::endl;

template<typename T>
class DynamicArray {
private:
    T *_data;
    size_t _size;
    size_t _capacity;

    void addCapacity() {
        size_t new_capacity = (_capacity == 0) ? 1 : _capacity * 2;
        T *new_data = new T[new_capacity];
        std::copy(_data, _data + _size, new_data);
        delete[] _data;
        _data = new_data;
        _capacity = new_capacity;
    }

public:
    class Iterator {
    private:
        T *_iter;
    public:
        Iterator() { _iter = nullptr; }

        explicit Iterator(T *data) { _iter = data; }

        ~Iterator() { _iter = nullptr; }

        T &operator*() { return *_iter; }

        const T &operator*() const { return *_iter; }

        void clear() { this->~Iterator(); }

        Iterator &operator=(const Iterator &other) {
            if (this == &other) {
                return *this;
            }
            _iter = other._iter;
            return *this;
        }

        Iterator &operator++() {
            ++_iter;
            return *this;
        }

        Iterator &operator--() {
            --_iter;
            return *this;
        }

        Iterator &operator+=(size_t size) {
            _iter += size;
            return *this;
        }

        Iterator &operator-=(size_t size) {
            _iter -= size;
            return *this;
        }

        Iterator operator+(size_t size) {
            Iterator temp = *this;
            temp._iter += size;
            return temp;
        }

        Iterator operator-(size_t size) {
            Iterator temp = *this;
            temp._iter -= size;
            return temp;
        }

        Iterator &operator[](size_t size) { return *(_iter + size); }

        bool operator==(const Iterator &other) { return _iter == other._iter; }

        bool operator!=(const Iterator &other) { return _iter != other._iter; }

        bool operator<(const Iterator &other) const { return _iter < other._iter; }

        bool operator>(const Iterator &other) const { return _iter > other._iter; }

        bool operator<=(const Iterator &other) const { return _iter <= other._iter; }

        bool operator>=(const Iterator &other) const { return _iter >= other._iter; }
    };

    DynamicArray() : _data(nullptr), _size(0), _capacity(0) {}

    DynamicArray(const DynamicArray<T> &array) {
        _size = array._size;
        _capacity = array._capacity;
        _data = new T[_capacity];
        std::copy(array._data, array._data + array._size, _data);
    }

    DynamicArray(const T value, size_t size) {
        _size = size;
        _capacity = _size;
        _data = new T[_capacity];
        for (int i = 0; i < _size; ++i) {
            _data[i] = 0;
        }
    }

    ~DynamicArray() {
        _size = 0;
        _capacity = 0;
        delete[] _data;
        _data = nullptr;
    }

    bool operator==(const DynamicArray<T> &right) {
        if (this->_capacity != right._capacity || this->_size != right._size)
            return false;

        bool isEqual = true;
        for (int i = 0; i < right._size; ++i) {
            if (right[i] != (*this)[i])
                isEqual = false;
        }
        return isEqual;
    }

    DynamicArray<T> &operator=(const DynamicArray<T> &right) {
        if (this == &right)
            return *this;
        delete _data;
        _size = right._size;
        _capacity = right._capacity;
        _data = new T[_capacity];
        std::copy(right._data, right._data + right._size, _data);
        return *this;
    }

    [[nodiscard]] constexpr T &operator[](int index) const {
        assert(index >= 0 && index < _size && _data != nullptr);
        return _data[index];
    }

    [[nodiscard]] constexpr Iterator begin() const { return Iterator(_data); }

    [[nodiscard]] constexpr Iterator end() const { return Iterator(&_data[_size]); }

    [[nodiscard]] constexpr T *data() const { return _data; }

    [[nodiscard]] constexpr size_t getSize() const { return _size; }

    [[nodiscard]] constexpr size_t getCapacity() const { return _capacity; }

    [[nodiscard]] constexpr bool isEmpty() const { return _size == 0; }

    constexpr void reserve(size_t capacity) {
        if (_capacity == 0) {
            _capacity = capacity;
            _data = new T[_capacity];
            return;
        }
        if (capacity > _capacity) {
            T *temp_data = new T[capacity];
            _capacity = capacity;
            std::copy(_data, _data + _size, temp_data);
            delete _data;
            _data = temp_data;
        }
    }

    constexpr void push_back(T data) {
        if (_size == _capacity)
            addCapacity();
        assert(_size < _capacity && _data != nullptr);
        _data[_size++] = data;
    }

    constexpr void pop_back() {
        if (_size == 0)
            return;
        //_data[_size - 1] = 0;

        --_size;
    }

    constexpr void swap(DynamicArray<T> &right) {
        std::swap(_size, right._size);
        std::swap(_capacity, right._capacity);
        std::swap(_data, right._data);
    }

    constexpr void clear() {
        this->~DynamicArray();
    }

    constexpr void printArray() {
        for (int i = 0; i < _size; ++i) {
            std::cout << _data[i] << ' ';
        }
        std::cout << std::endl;
    }
};


template<typename T>
struct DefaultComparator {
    bool operator()(const T &left, const T &right) const {
        return left < right;
    }
};


template<typename T>
struct XDDComparator {
    bool operator()(const T &left, const T &right) const {
        return left > right;
    }
};

template<typename T>
struct Descriptor{
    T *_array;
    size_t _index;

    Descriptor() : _array(nullptr), _index(0){}

    explicit Descriptor(T* array){
        _array = array;
        _index = 0;
    }

    ~Descriptor(){
        _array = nullptr;
    }

    [[nodiscard]] constexpr T &operator[](int idx) const {
        //assert(idx >= 0 && idx < _array && _array != nullptr); ///TODO: ????
        return &_array[idx];
    }

//    Descriptor& operator=(const Descriptor<T>& other) {
//        if (this != &other) {
//            _array = other._array;
//            _index = other._index;
//        }
//        return *this;
//    }

    bool operator==(const Descriptor<T> &other) { return _array[_index] == other._array[other._index]; }

    bool operator!=(const Descriptor<T> &other) { return _array[_index] != other._array[other._index]; }

    bool operator<(const Descriptor<T> &other) const { return _array[_index] < other._array[other._index]; }

    bool operator>(const Descriptor<T> &other) const { return _array[_index] > other._array[other._index]; }

    bool operator<=(const Descriptor<T> &other) const { return _array[_index] <= other._array[other._index]; }

    bool operator>=(const Descriptor<T> &other) const { return _array[_index] >= other._array[other._index]; }
};

template<typename T, typename Comparator = DefaultComparator<T>>
class Heap {
private:
    DynamicArray<T> _array;
    Comparator _comparator;

    void siftUp(int index) {
        while (index > 0) {
            int parent = (index - 1 ) / 2;
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

    Heap(const Heap &heap) = delete;

    Heap(Heap &&) = delete;

    ~Heap() {
        _array.clear();
    }

    Heap &operator=(const Heap &heap) = delete;

    Heap &operator=(Heap &&heap) = delete;

    [[nodiscard]] const T& top() const {
        return _array[0];
    }

    void push(const T& element) {
        _array.push_back(element);
        siftUp(_array.getSize() - 1);
    }


    void pop() {
        if (!_array.isEmpty()){
            /// TODO: OWN STD SWAP -> temp descriptor
            std::swap(_array[0], _array[_array.getSize() - 1]);
            _array.pop_back();
            if( !_array.isEmpty() ) {
                siftDown(0);
            }
        }
    }
};

void parseIO(std::istream& input_stream, std::ostream& output_stream, Heap<Descriptor<int>>& heap){
    int array_count, array_size, element;
    input_stream >> array_count;
    for (int i = 0; i < array_count; ++i) {
        input_stream >> array_size;
        int* temp_array = new int[array_size];
        for (int j = 0; j < array_size; ++j) {
            input_stream >> element;
            temp_array[j] = element;
        }
        Descriptor<int> descriptor(temp_array);
        heap.push(descriptor);
    }
}

int main() {
    Heap<Descriptor<int>> heap;
    parseIO(std::cin, std::cout, heap);
    std::cout << heap.top()._array[heap.top()._index] << ' ';
    std::cout << heap.top()._array[heap.top()._index + 1] << ' ';
    std::cout << heap.top()._array[heap.top()._index + 2] << ' ';
    heap.pop();
    std::cout << heap.top()._array[heap.top()._index] << ' ';

    return 0;
}