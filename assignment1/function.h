#pragma once
#pragma once

#include <iostream>
#include <vector>
#include <algorithm> // gotta use swap
#include <chrono>    // for timing
using namespace std;

// This Min-Heap class uses the basic array layout.
class MinHeap {
private:
    vector<int> data;



    // Index helpers
    int parent(int j) const { return (j - 1) / 2; }

    int left(int j) const { return 2 * j + 1; }

    int right(int j) const { return 2 * j + 2; }






    // Percolate UP (insert one-by-one)
    void upheap(int j) {
        while (j > 0 && data[j] < data[parent(j)]) {
            swap(data[j], data[parent(j)]);
            j = parent(j);
        }
    }




    // Percolate DOWN 
    void downheap(int j) {

        int n = data.size();

        while (true) {

            int l = left(j);
            int r = right(j);
            int smallest = j;


            // Find smallest child
            if (l < n && data[l] < data[smallest]) smallest = l;
            if (r < n && data[r] < data[smallest]) smallest = r;



            // Stop if it's already a heap
            if (smallest == j) break;


            swap(data[j], data[smallest]);
            j = smallest;
        }
    }




public:
	//(A) Build insertion (O(N log N)).
    void buildHeapUp(const vector<int>& values) {
        data.clear();
        for (int v : values) {
            data.push_back(v);
            upheap(data.size() - 1);
        }
    }

	// (B) Build heapify (O(N)).
    void buildHeapDown(const vector<int>& values) {
        data = values;
        if (data.empty()) return;

        int start = parent(data.size() - 1);
        for (int j = start; j >= 0; j--) {
            downheap(j);
        }
    }





    void printHeap() const {
        for (int v : data) cout << v << " ";
        cout << "\n";
    }

};
