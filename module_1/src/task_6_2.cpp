#include "../include/MinMax.hpp"
#include <iostream>

template <typename T>
using comp_func = bool (*)(const T& l, const T& r);

template <typename T>
T median_of_three(T* array, int left, int right) {
    int a = array[left];
    int b = array[left + (right - left) / 2];
    int c = array[right - 1];
    int median = max(min(a, b), min(max(a, b), c));
    return ((median == a) ? left : ((median == b) ? left + (right - left) / 2 : right - 1));
}

template <typename T>
int partition(int* array, int left, int right, comp_func<T> comp) {
    int pivot_idx = median_of_three(array, left, right);

    std::swap(array[pivot_idx], array[left]);
    T& pivot = array[left];
    int j = right - 1;
    int i = right;
    while (j > left) {
        if (!comp(array[j], pivot)) {
            --i;
            std::swap(array[i], array[j]);
        }
        --j;
    }

    std::swap(array[i - 1], array[left]);
    return i - 1;
}

template <typename T>
int kth_element(T* array, size_t size, int k, comp_func<T> comp) {
    int left = 0;
    int right = size;
    while (left <= right) {
        int m = partition(array, left, right, comp);
        if (m == k)
            return array[m];
        else if (k < m)
            right = m;
        else
            left = m + 1;
    }
}

bool defaultCompFunc(const int& l, const int& r) {
    return l < r;
}

namespace task_6_2 {
    void IO(std::istream& input_stream, std::ostream& output_stream) {
        int array_size;
        input_stream >> array_size;
        int array[array_size];
        for (int i = 0; i < array_size; ++i)
            input_stream >> array[i];
        

        int tenth_percent = static_cast<int>(array_size * 0.1f);
        int ninetieth_percent = static_cast<int>(array_size * 0.9f);
        int median = array_size / 2;
        output_stream << kth_element(array, array_size, tenth_percent, defaultCompFunc) << '\n'
                  << kth_element(array, array_size, median, defaultCompFunc) << '\n'
                  << kth_element(array, array_size, ninetieth_percent, defaultCompFunc);
    }
}