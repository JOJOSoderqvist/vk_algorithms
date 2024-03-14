#include <cstddef>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <vector>

template<typename T>
class DynamicArray{
private:
    T* _data;
    size_t _size;
    size_t _capacity;
    void addCapacity(){
        size_t new_capacity = (_capacity == 0) ? 1 : _capacity * 2;
        T* new_data = new T[new_capacity];
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
    DynamicArray() : _data(nullptr), _size(0), _capacity(0){}
    ~DynamicArray(){
        delete[] _data;
    }
    [[nodiscard]] size_t getSize() const { return _size; }
    [[nodiscard]] size_t getCapacity() const { return _capacity; }
    [[nodiscard]] T operator[](int index) const { return getAt(index);}

    void add(T data){
        if (_size == _capacity)
            addCapacity();
        assert(_size < _capacity && _data != nullptr);
        _data[_size++] = data;
    }

    void printArray(){
        for (int i = 0; i < _size; ++i) {
            std::cout << _data[i] << ' ';
        }
        std::cout << std::endl;
    }
};

int main(){
    DynamicArray<int> array;
    array.add(23);
    array.add(12);
    array.add(35);
    array.add(36);
    array.add(37);
    array.printArray();
    std::cout << array.getCapacity() << "  " << array.getSize() << "  " << array[2];
}