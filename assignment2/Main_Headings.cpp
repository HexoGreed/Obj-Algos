/*
* Hamza Shah
* csc 255
* 9/27
* ^^ i forgot to do the QA
QA:

After running each of the sorting algos 5 times each
on arrays of 5000 random integers the results / timings were
generally the same as the expected / theoretical times / rankings

Insertion sort was by far the slowest taking the most time out of them all
this alligns becase insertion sort is O(n ^ 2) in the average and worst case scenarios
and O(n) in the best case scenario, with the input being 5000
random integers one can see why this would be a problem.

The faster algorithims were merge sort and quick sort,
completing the task in mere miliseconds.Heap sort was slightly
slower than quick sort but was still typically within
.500 milliseconds of quick sort.

The reason why quick sort performed the best is because
it has an average time complexity of O(n log n)
the same as merge sort.
However quick sort is typically faster in practice
this is because quick sort keeps everything typically
within the array and doesnt require additional memory allocation
like merge sort does when it creates the left and right temp arrays.
this means, that although small, it has a better performance overall.




*/



















#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "Headings.h"
using namespace std;






//time functions
chrono::high_resolution_clock::time_point startTime() {
    return chrono::high_resolution_clock::now();
}

long long stopTime(chrono::high_resolution_clock::time_point start) {
    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::nanoseconds>(end - start).count();
}





int main() {
    srand(time(0)); // seed random


    int size = 5000;
    int runs = 5;

    vector<long long> insertionTimes, mergeTimes, quickTimes, heapTimes;


    for (int i = 0; i < runs; i++) {

        vector<int> baseVec(size);

        for (int j = 0; j < size; j++) {

            baseVec[j] = rand() % (size * 10) + 1;
        }



         

        //ignore this part its just all copy paste VVVV

        // insertion sort
        for (int i = 0; i < runs; i++) {
            cout << "\n== Run " << (i + 1) << " ===\n";

            // Create random vector
            vector<int> baseVec(size);
            for (int j = 0; j < size; j++) {
                baseVec[j] = rand() % (size * 10) + 1;
            }

            vector<int> a;
            long long timeTaken;
            auto start = startTime();



            // Insertion Sort
            a = baseVec;
            start = startTime();
            Insert_sort(a);
            timeTaken = stopTime(start);
            insertionTimes.push_back(timeTaken);
			cout << "Insert_sort time: " << timeTaken / 1e6 << " ms\n"; // convert ns to ms 


            
            // Merge Sort
            a = baseVec;
            start = startTime();
            Merge(a);
            timeTaken = stopTime(start);
            mergeTimes.push_back(timeTaken);
            cout << "Merge time:       " << timeTaken / 1e6 << " ms\n";



            // Quick Sort
            a = baseVec;
            start = startTime();
            Quick_Sort(a, 0, a.size() - 1);
            timeTaken = stopTime(start);
            quickTimes.push_back(timeTaken);
            cout << "Quick_Sort time:  " << timeTaken / 1e6 << " ms\n";




            // Heap Sort
            a = baseVec;
            start = startTime();
            Heap_sort(a);
            timeTaken = stopTime(start);
            heapTimes.push_back(timeTaken);
            cout << "Heap_sort time:   " << timeTaken / 1e6 << " ms\n";

        }


		// end of copy paste ^^^^
    }





    auto avg = [](const vector<long long>& t) {
        long long sum = 0;
        for (auto n : t) sum += n;
        return (double)sum / t.size();
        };



    cout << "\nAverage runtimes: " << runs << " runs (size " << size << "):\n";
    cout << "Insertion: " << avg(insertionTimes) / 1e6 << " ms\n";
    cout << "Merge:     " << avg(mergeTimes) / 1e6 << " ms\n";
    cout << "Quick:     " << avg(quickTimes) / 1e6 << " ms\n";
    cout << "Heap:      " << avg(heapTimes) / 1e6 << " ms\n";

    return 0;
}
