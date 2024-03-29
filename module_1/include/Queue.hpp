#include "DynamicArray.hpp"

class Queue {
private:
    DynamicArray<int> array;
    int head;
    int tail;
    int array_size;
public:
    explicit Queue(int size) : head(0), tail(0), array_size(size), array(0, size) {}
    ~Queue(){
        array.clear();
        head = 0;
        tail = 0;
    }

    void Enqueue(int elem){
        array[tail] = elem;
        ++tail;
        if (tail == array_size) {
            tail = 0;
        }
    }

    int Dequeue(){
        if (head == tail) {
            return -1;
        }
        int value = array[head];
        ++head;
        if (head == array_size) {
            head = 0;
        }
        return value;
    }
};