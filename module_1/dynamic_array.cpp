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
        delete[] _data;
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

    [[nodiscard]] T operator[](int index) const { return getAt(index); }

    [[nodiscard]] T& front() const { return _data[0]; }

    [[nodiscard]] T& back() const { return _data[_size - 1]; }

    [[nodiscard]] T* data() const { return front(); }

    [[nodiscard]] size_t getSize() const { return _size; }

    [[nodiscard]] size_t getCapacity() const { return _capacity; }

    [[nodiscard]] bool isEmpty() const { return _size == 0; }

    void reserve(size_t capacity){
        if (_capacity == 0) {
            _capacity = capacity;
            _data = new T[_capacity];
            return;
        }
        if (capacity > _capacity){
            T* temp_data = new T[capacity];
            _capacity = capacity;
            std::copy(_data, _data + _size, temp_data);
            delete _data;
            _data = temp_data;
        }
    }


    void oush_back(T data) {
        if (_size == _capacity)
            addCapacity();
        assert(_size < _capacity && _data != nullptr);
        _data[_size++] = data;
    }

    void printArray() {
        for (int i = 0; i < _size; ++i) {
            std::cout << _data[i] << ' ';
        }
        std::cout << std::endl;
    }
};

int main() {
//    DynamicArray<int> array;
//    array.reserve(10);
//    array.oush_back(23);
//    array.oush_back(12);
//    array.oush_back(12);
//    array.oush_back(12);
//
//    std::cout << array.getSize() << ' ' << array.getCapacity() << ' ' << array.data();
//
//    array.reserve(50);
//    std::cout << '\n';
//    std::cout << array.getSize() << ' ' << array.getCapacity() << ' ' << array.data();
}