#include <cstdio>
#include <iostream>

void print_arr(int* arr, int count) {
    std::cout << "arr is: ";
    for (int index = 0; index < count; index++) 
        std::cout << arr[index] << " ";
    std::cout << std::endl;
}

void swap(int& first, int& second) {
    int tmp = first;
    first = second;
    second = tmp;
}

void select_sort(int* arr, int count) {
    for (int index = 0; index < count - 1; index++) {
        for (int jdex = index +1; jdex < count; jdex++) {
            if (arr[index] > arr[jdex]) 
                swap(arr[index], arr[jdex]);
        }
    }
} 

void bubble_sort(int* arr, int count) {
    for (int index = 0; index < count - 1; index++) {
        for (int jdex = 0; jdex < count - 1 - index; jdex++) {
            if (arr[jdex] > arr[jdex + 1])
                swap(arr[jdex], arr[jdex + 1]);
        }
    }
}

void insert_sort(int* arr, int count) {
    for (int index = 1, jdex; index < count; index++) {
        int tmp = arr[index];
        for (jdex = index; jdex > 0 && tmp < arr[jdex - 1]; jdex--)
            arr[jdex] = arr[jdex - 1];
        arr[jdex] = tmp;
    }
}

void shell_sort(int* arr, int count) {
    for (int inc = count / 2, jdex; inc > 0; inc /= 2) {
        for (int index = inc; index < count; index+= inc) {
            int tmp = arr[index];
            for (jdex = index; jdex > 0 && tmp < arr[jdex - inc]; jdex -= inc)
                arr[jdex] = arr[jdex - inc];
            arr[jdex] = tmp;
        }
    }
}

void quick_sort(int* arr, int left, int right) {
    if (left >= right) 
        return;
    int pre_left = left;
    int pre_right = right;
    int prvot = arr[left];
    while (left < right) {
        while (left < right && arr[right] >= prvot)
            right--;
        if (left < right)
            arr[left] = arr[right];
        while (left < right && arr[left] <= prvot)
            left++;
        if (left < right)
            arr[right] = arr[left];
    }
    if (left >= right) 
        arr[left] = prvot;
    quick_sort(arr, pre_left, right - 1);
    quick_sort(arr, right + 1, pre_right);
}

void heapify(int* arr, int count, int index) {
    int largest = index;
    int left_son = 2 * index + 1;
    int right_son = 2 * index + 2;
    if (left_son < count && arr[largest] < arr[left_son])
        largest = left_son;
    if (right_son < count && arr[largest] < arr[right_son])
        largest = right_son;
    if (largest != index) {
        swap(arr[index], arr[largest]);
        heapify(arr, count, largest);
    }
}

void heap_sort(int* arr, int count) {
    int n;
    for (n = count/2 - 1; n >= 0; n--)
        heapify(arr, count, n);
    
    for (n = count - 1; n > 0; n--) {
        swap(arr[n], arr[0]);
        heapify(arr, n, 0);
    }
}

void test_select_sort() {
    int arr[6] = {5, 1, 2, 3, 4, 6};
    select_sort(arr, 6);
    print_arr(arr, 6);
}

void test_bubble_sort() {
    int arr[6] = {5, 1, 2, 3, 4, 6};
    bubble_sort(arr, 6);
    print_arr(arr, 6);
}

void test_insert_sort() {
    int arr[6] = {5, 1, 2, 3, 4, 6};
    insert_sort(arr, 6);
    print_arr(arr, 6);    
}

void test_shell_sort() {
    int arr[6] = {5, 1, 2, 3, 4, 6};
    shell_sort(arr, 6);
    print_arr(arr, 6);    
}

void test_quick_sort() {
    int arr[6] = {5, 1, 2, 3, 4, 6};
    quick_sort(arr, 0, 5);
    print_arr(arr, 6);    
}

void test_heap_sort() {
    int arr[6] = {5, 1, 2, 3, 4, 6};
    heap_sort(arr, 6);
    print_arr(arr, 6);    
}

int main() {
    test_select_sort();
    test_bubble_sort();
    test_insert_sort();
    test_shell_sort();
    test_quick_sort();
    test_heap_sort();
    return 1;
}