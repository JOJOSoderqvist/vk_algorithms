#include "../include/DynamicArray.hpp"
#include <iostream>

template <typename T>
using comp_func = bool (*)(const T& l, const T& r);

template <typename T>
int partition(DynamicArray<T>& array, int left, int right, comp_func<T> comp) {
    int pivot_idx = left + (right - left) / 2;
    T& pivot = array[pivot_idx];
    std::swap(array[pivot_idx], array[right - 1]);
    int i = left;
    int j = right - 1;
    while (i < j) {
        for (; comp(array[i], pivot); ++i);
        for (; !comp(array[j], pivot); --j);

        if (i < j){
            std::swap(array[i], array[j]);
            ++i;
            --j;
        }
    }

    std::swap(array[i], array[right - 1]);
    return i;
}

template <typename T>
void kth_element(DynamicArray<T>& array, int k, comp_func<T> comp) {
    int left = 0;
    int right = array.getSize();
    while (left <= right) {
        int m = partition(array, left, right, comp);
        if (m == k) 
            return;
        else if (k < m) 
            right = m;
        else
            left = m + 1;
    }
}

bool defaultCompFunc(const int& l, const int& r){
    return l < r;
}

namespace task_6_2 {
    void IO(std::istream& input_stream, std::ostream& output_stream) {
        DynamicArray<int> array;
        array.pushBack(2);
        array.pushBack(1);
        array.pushBack(10);
        array.pushBack(8);
        array.pushBack(7);

        kth_element(array, 7, defaultCompFunc);
    }
}