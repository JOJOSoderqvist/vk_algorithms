#include "../include/MinMax.hpp"
#include <cassert>
#include <iostream>

void counting_sort(int* array, size_t array_size) {
    assert(array_size > 0 && array != nullptr);
    int minVal = array[0];
    int maxVal = array[0];

    for (int i = 0; i < array_size; ++i) {
        minVal = min(minVal, array[i]);
        maxVal = max(maxVal, array[i]);
    }

    int bufSize = maxVal - minVal + 1;
    int* buf = new int[bufSize]();
    for (int i = 0; i < array_size; ++i) {
        buf[array[i] - minVal]++;
    }

    for (int i = 1; i < bufSize; ++i) {
        buf[i] += buf[i - 1];
    }

    int* tmp = new int[array_size];

    for (int i = array_size - 1; i >= 0; --i)    {
        int bufPos = array[i] - minVal;
        buf[bufSize]--;
        tmp[buf[bufPos]] = array[i];
    }
    for (int i = 0; i < array_size; ++i)
    {
        array[i] = tmp[i];
    }
    
    delete[] tmp;
    delete[] buf;
}

void solve(int* array, size_t size){
    
}

namespace task_7_2 {
    void IO(std::istream& input_stream, std::ostream& output_stream) {
        int n;

        input_stream >> n;
        int* array = new int[n];

        for (int i = 0; i < n; ++i) {
            input_stream >> array[i];
        }

        counting_sort(array, n);

        for (int i = 0; i < n; ++i) {
            output_stream << array[i] << ' ';
        }
        delete[] array;
    }
}