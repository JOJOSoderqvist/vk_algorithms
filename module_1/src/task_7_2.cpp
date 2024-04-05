#include "../include/MinMax.hpp"
#include <cassert>
#include <iostream>

// void counting_sort(int* array, size_t array_size) {
//     assert(array_size > 0 && array != nullptr);
//     int minVal = array[0];
//     int maxVal = array[0];

//     for (int i = 0; i < array_size; ++i) {
//         minVal = min(minVal, array[i]);
//         maxVal = max(maxVal, array[i]);
//     }

//     int bufSize = maxVal - minVal + 1;
//     int* buf = new int[bufSize]();
//     for (int i = 0; i < array_size; ++i) {
//         buf[array[i] - minVal]++;
//     }

//     for (int i = 1; i < bufSize; ++i) {
//         buf[i] += buf[i - 1];
//     }

//     int* tmp = new int[array_size];

//     for (int i = array_size - 1; i >= 0; --i)    {
//         int bufPos = array[i] - minVal;
//         buf[bufSize]--;
//         tmp[buf[bufPos]] = array[i];
//     }
//     for (int i = 0; i < array_size; ++i)
//     {
//         array[i] = tmp[i];
//     }
    
//     delete[] tmp;
//     delete[] buf;
// }

int digit(long long x, int i) {
    return (x >> (8 * i)) & 255;
}

void LSDSort(long long* arr, size_t size) {
    assert(arr != nullptr && size > 0);
    const char digits_number = 8; 
    const short max_single_digit_value = 256;
    long long* temp = new long long[size];
    int* counting_array = new int[max_single_digit_value];

    for (int i = 0; i < digits_number; ++i) {

        for (int j = 0; j < max_single_digit_value; ++j)
            counting_array[j] = 0;

        for (int j = 0; j < size; ++j) {
            int d = digit(arr[j], i);
            ++counting_array[d];
        }

        int count = 0;
        for (int j = 0; j < max_single_digit_value; ++j) {
            int temp = counting_array[j];
            counting_array[j] = count;
            count += temp;
        }

        for (int j = 0; j < size; ++j) {
            int d = digit(arr[j], i);
            temp[counting_array[d]] = arr[j];
            ++counting_array[d];
        }

        for (int j = 0; j < size; ++j) 
            arr[j] = temp[j];
    }   

    delete[] temp;
    delete[] counting_array;
}

namespace task_7_2 {
    void IO(std::istream& input_stream, std::ostream& output_stream) {
        int n;
        input_stream >> n;
        long long array[n];
        for (int i = 0; i < n; ++i)
            input_stream >> array[i];
        LSDSort(array, n);
         for (int i = 0; i < n; ++i)
            output_stream << array[i] << ' ';
    }
}