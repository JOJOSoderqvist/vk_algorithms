#include <cassert>
#include <algorithm>
#include <iostream>
#include <vector>

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

    [[nodiscard]] T getAt(int index) const {
        assert(index >= 0 && index < _size && _data != nullptr);
        return _data[index];
    }

public:
    DynamicArray() : _data(nullptr), _size(0), _capacity(0) {}

    DynamicArray(const DynamicArray<T> &array) {
        _size = array._size;
        _capacity = array._capacity;
        _data = new T[_capacity];
        std::copy(array._data, array._data + array._size, _data);
    }

    DynamicArray(const T &array, size_t size) {
        _size = size;
        _capacity = _size;
        _data = new T[_capacity];
        std::copy(array._data, array._data + array._size, _data);
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

    [[nodiscard]] constexpr T operator[](int index) const { return getAt(index); }

    [[nodiscard]] constexpr T& front() const { return _data[0]; }

    [[nodiscard]] constexpr T& back() const { return _data[_size - 1]; }

    [[nodiscard]] constexpr T* data() const { return &front(); }

    [[nodiscard]] constexpr size_t getSize() const { return _size; }

    [[nodiscard]] constexpr size_t getCapacity() const { return _capacity; }

    [[nodiscard]] constexpr bool isEmpty() const { return _size == 0; }

    constexpr void reserve(size_t capacity){
        if (_capacity == 0) {
            _capacity = capacity;
            _data = new T[_capacity];
            return;
        }
        if (capacity > _capacity){
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

    constexpr void printArray() {
        for (int i = 0; i < _size; ++i) {
            std::cout << _data[i] << ' ';
        }
        std::cout << std::endl;
    }

    constexpr void clear(){
        this->~DynamicArray();
    }

    constexpr void swap(DynamicArray<T>& right){
        std::swap(_size, right._size);
        std::swap(_capacity, right._capacity);
        std::swap(_data, right._data);
    }
};

int main() {
    DynamicArray<int> array;
    array.push_back(1);
    array.push_back(2);
    array.push_back(3);

    DynamicArray<int> second_array;
    second_array.push_back(4);
    second_array.push_back(5);
    second_array.push_back(6);
    array.swap(second_array);

    array.printArray();
    second_array.printArray();
}