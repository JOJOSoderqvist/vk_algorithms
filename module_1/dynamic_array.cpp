#include <cassert>
#include <algorithm>
#include <iostream>
#include <vector>

#define PRINT_ARRAY_INFO(array) std::cout << "Size: " << array.getSize() << ", Capacity: " << array.getCapacity() << std::endl;

template<typename T1, typename T2>
struct pair{
    T1 _first;
    T2 _second;

    pair() = default;

    pair(T1 first, T2 second){
        this->makePair(first, second);
    }

    void makePair(T1 first, T2 second){
        _first = first;
        _second = second;
    }
};


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

        void clear(){ this->~Iterator(); }

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

    DynamicArray(DynamicArray<T> && other) noexcept {
        _data = other._data;
        _size = other._size;
        _capacity = other._capacity;

        other._data = nullptr;
        other._capacity = 0;
        other._size = 0;
    }


    DynamicArray<T>& operator=(DynamicArray<T>&& other) noexcept {
        if (this != &other) {
            delete[] _data;
            _data = other._data;
            _size = other._size;
            _capacity = other._capacity;
            other._data = nullptr;
            other._size = 0;
            other._capacity = 0;
        }
        return *this;
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

    [[nodiscard]] constexpr T& operator[](int index) const {
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


int main() {
//    DynamicArray<int> array(0, 2);
//    PRINT_ARRAY_INFO(array)
//    std::cout << '\n';
//    for (const auto elem:array) {
//        std::cout << elem;
//    }


    DynamicArray<pair<int, int>> a;
    a.push_back({1, 2});
    a.push_back({2, 3});
    for (auto elem: a) {
        std::cout << elem._first << ' ' << elem._second;
    }
}