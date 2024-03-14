#include <iostream>
#include <cassert>

bool binarySearch(const int* arr, int key, int left_bound, int right_bound) {
    int result = -1;
    while (left_bound <= right_bound){
        int mid_elem_index = (left_bound + right_bound) / 2;
        int mid_elem = arr[mid_elem_index];
        if (mid_elem >= key){
            result = mid_elem_index;
            right_bound = mid_elem_index - 1;
        } else {
            left_bound = mid_elem_index + 1;
        }
    }
    if (result != -1) {
        std::cout << result;
        return true;
    }
    return false;
}

void exponentialSearch(const int* arr, int size, int key) {

    int right_bound = 1;
    while (right_bound < size && arr[right_bound] < key) {
        right_bound *= 2;
    }
    if (!binarySearch(arr, key, right_bound/2, std::min(right_bound, size)))
        std::cout << size;
}

void IO(std::istream& input_stream){
    int m, n;
    input_stream >> m >> n;
    assert(m > 0 && n > 0);
    int a[m], b[n];
    for (int i = 0; i < m; ++i) {
        input_stream >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        input_stream >> b[i];
    }
    for (int i = 0; i < n; ++i) {
        exponentialSearch(a, m, b[i]);
    }
}

int main(){
    IO(std::cin);
}