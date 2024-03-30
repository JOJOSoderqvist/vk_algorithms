#include "../include/DynamicArray.hpp"

#include <iostream>

struct PointDescriptor {
    int coord;
    bool isSectionStarted;

    PointDescriptor() : coord(0), isSectionStarted(false) {}

    PointDescriptor(int coord, bool isSectionStarted) : coord(coord), isSectionStarted(isSectionStarted) {}

    PointDescriptor(const PointDescriptor& other) : coord(other.coord), isSectionStarted(other.isSectionStarted) {}
    ~PointDescriptor() = default;

    PointDescriptor& operator=(const PointDescriptor& other) {
        if (this == &other) {
            return *this;
        }
        coord = other.coord;
        isSectionStarted = other.isSectionStarted;
        return *this;
    }

    bool operator<=(const PointDescriptor& other) const {
        return coord <= other.coord;
    }
};

template <typename T>
using compFunc = bool (*)(const T&, const T&);

bool defaultComparatorFunc(const PointDescriptor& l, const PointDescriptor& r) {
    return l <= r;
}

template <typename T>
void merge(DynamicArray<T>& array, int left, int mid, int right, compFunc<T> comparator_func) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    DynamicArray<T> L(n1), R(n2);

    for (i = 0; i < n1; i++)
        L[i] = array[left + i];
    for (j = 0; j < n2; j++)
        R[j] = array[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (comparator_func(L[i], R[j])) {
            array[k] = L[i];
            i++;
        } else {
            array[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        array[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        array[k] = R[j];
        j++;
        k++;
    }
}

template <typename T>
void mergeSort(DynamicArray<T>& array, int n, compFunc<T> comparator_func = defaultComparatorFunc) {
    int curr_size;
    int left_start;

    for (curr_size = 1; curr_size <= n - 1; curr_size = 2 * curr_size) {
        for (left_start = 0; left_start < n - 1; left_start += 2 * curr_size) {
            int mid = std::min(left_start + curr_size - 1, n - 1);
            int right_end = std::min(left_start + 2 * curr_size - 1, n - 1);

            merge(array, left_start, mid, right_end, comparator_func);
        }
    }
}

DynamicArray<PointDescriptor> parseArrayFromIO(std::istream& input_stream) {
    int array_number, point_coord;
    bool is_section_started;
    DynamicArray<PointDescriptor> point_descriptor_array;
    input_stream >> array_number;
    for (size_t i = 0; i < array_number; ++i) {
        input_stream >> point_coord;
        PointDescriptor descriptor(point_coord, true);
        point_descriptor_array.pushBack(descriptor);

        input_stream >> point_coord;
        descriptor = PointDescriptor(point_coord, false);
        point_descriptor_array.pushBack(descriptor);
    }
    return point_descriptor_array;
}

void solve(DynamicArray<PointDescriptor>& point_descriptor_array, std::ostream& output_stream) {
    assert(point_descriptor_array.getSize() > 0);
    int total_filled = 0, section_id = 0, point_coord = 0;
    mergeSort(point_descriptor_array, point_descriptor_array.getSize());

    for (const auto& point_descriptor : point_descriptor_array) {
        int old_section_id = section_id;
        int old_point_coord = point_coord;
        point_coord = point_descriptor.coord;
        point_descriptor.isSectionStarted ? ++section_id : --section_id;

        if (old_section_id != 0) {
            total_filled += point_descriptor.coord - old_point_coord;
        }
    }

    std::cout << total_filled;
}

namespace task_5_3 {
    void IO(std::istream& input_stream, std::ostream& output_stream) {
        DynamicArray<PointDescriptor> point_descriptor_array = parseArrayFromIO(input_stream);
        solve(point_descriptor_array, output_stream);
        std::cout << std::endl;
    }
}