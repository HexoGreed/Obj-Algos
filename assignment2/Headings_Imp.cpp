













#pragma once

#include "Headings.h"
#include <algorithm> // for swap

//helper functions
// 
// 
// 
// For Merge Sort
static void merge(std::vector<int>& arr, const std::vector<int>& left, const std::vector<int>& right) {
    size_t i = 0, j = 0, k = 0;
    while (i < left.size() && j < right.size()) {

        if (left[i] <= right[j]) {

            arr[k++] = left[i++];

        } else {

            arr[k++] = right[j++];
        }
    }
    while (i < left.size()) {
        arr[k++] = left[i++];
    }
    while (j < right.size()) {
        arr[k++] = right[j++];
    }
}




// For Quick Sort

static int Parting(std::vector<int>& arr, int begin, int end) {
    int pivot = arr[end];
    int i = (begin - 1);
    for (int j = begin; j < end; j++) {

        if (arr[j] <= pivot) {

            i++;
            std::swap(arr[i], arr[j]);

        }
    }


    std::swap(arr[i + 1], arr[end]);
    return i + 1;
}



// For Heap Sort
static void heapify(std::vector<int>& arr, int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}
//end of helper functions









//sorting algos
void Insert_sort(std::vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {

            arr[j + 1] = arr[j];
            j = j - 1;

        }

        arr[j + 1] = key;
    }
}



void Merge(std::vector<int>& arr) {

    if (arr.size() < 2) return;

    size_t mid = arr.size() / 2;
    std::vector<int> left(arr.begin(), arr.begin() + mid);
    std::vector<int> right(arr.begin() + mid, arr.end());

    Merge(left);
    Merge(right);
    merge(arr, left, right);
}

void Quick_Sort(std::vector<int>& arr, int begin, int end) {

    if (begin < end) {
        int PartingIndex = Parting(arr, begin, end);
        Quick_Sort(arr, begin, PartingIndex - 1);
        Quick_Sort(arr, PartingIndex + 1, end);
    }

}


void Heap_sort(std::vector<int>& arr) {

    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }

}
