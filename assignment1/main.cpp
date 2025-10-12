/*
Hamza Shah
9/22/2025 - 10/5/2025 (doing the questions)



3.1.B)
The two methods are quite different when it comes to efficeny. Percolate down (heapify)
builds in linear time (O(n)) making it better for proccessing a list of 5000 items.
Its consistently faster than percolate up (insertion) wich is O(NlogN) because every element 
inserted requires up to log N operations.

The input order does not affect the performance of either method significantly.

The sorted data is the best case for percolate up (insertion) because each new element is larger than the last
meaning it barely has to do its job.

Reverse sorted data is the worst case for percolate up (insertion) because each new element is smaller than the last
It has to do the max amount of work.

The insertion method is only more efficient when dealing with incremental updates. 
If you already have a large heap and only need to add a few new items (K)
performing K insertions (O(KlogN) total time) is faster than repeatedly running the full O(N) 
heapify process on the entire structure.

TLDR: Percolate down (heapify) is better than percolate up.


//

*/



#include "function.h"
#include <iostream>
#include <vector>
#include <numeric>   // (iota, fills with 1, 2,3 ....)
#include <algorithm> // for std::reverse and std::shuffle (Reverses order of elements & shuffles elements)
#include <random>    // for std::mt19937 and std::random_device
#include <cstdlib>   // for srand, rand
#include <ctime>     // for time

using namespace std;

// quick helper function to run a timing test and print the results
void runTimingTest(const vector<int>& data, const string& dataType, bool usePercolateUp) {
    MinHeap heap;

	// start the clock
    auto start = chrono::high_resolution_clock::now();

    if (usePercolateUp) {
        heap.buildHeapUp(data);
    }
    else {
        heap.buildHeapDown(data);
    }

    // Get the clock time after it's done
    auto stop = chrono::high_resolution_clock::now();

    // Calculate the difference in ms
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);




    cout << "  Using " << (usePercolateUp ? "Percolate Up" : "Percolate Down")
        << ": " << duration.count() << " microseconds." << endl;
}


int main() {

    srand(time(0));


    vector<int> initial_values = { 2, 45, 12, 1, 56, 78, 13, 14, 5, 8, 9, 3, 11, 34 };

    cout << "Heap tests" << endl;
    MinHeap h1;
    h1.buildHeapUp(initial_values);
    cout << "Heap (percolate up):   ";
    h1.printHeap();



    MinHeap h2;
    h2.buildHeapDown(initial_values);
    cout << "Heap (percolate down): ";
    h2.printHeap();
    cout << "\n\n\n" << endl;





    //part 2
    const int N = 50000;
    cout << "Time test for "  << N << " ints" << endl;

    vector<int> sorted_data(N);
    iota(sorted_data.begin(), sorted_data.end(), 1); 



    //reverse dta
    vector<int> reverse_data = sorted_data;
    reverse(reverse_data.begin(), reverse_data.end());

    // 3. Make the random data
    vector<int> random_data = sorted_data;
    random_shuffle(random_data.begin(), random_data.end());






    //-------------------------------------------------------




    cout << "1. Testing with Sorted Data:" << endl;
    runTimingTest(sorted_data, "Sorted", true);  // Percolate Up
    runTimingTest(sorted_data, "Sorted", false); // Percolate Down
    cout << endl;







    cout << "2. Testing with Reverse-Sorted Data:" << endl;
    runTimingTest(reverse_data, "Reverse-Sorted", true);
    runTimingTest(reverse_data, "Reverse-Sorted", false);
    cout << endl;









    cout << "3. Testing with Random Data:" << endl;
    runTimingTest(random_data, "Random", true);
    runTimingTest(random_data, "Random", false);
    cout << endl;

    return 0;
}
