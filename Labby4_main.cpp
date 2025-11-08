/*
Hamza
Lab 4 assignment 1




QA:

3.)

The simulation, which involved 1000 insertions into a hash table of size 1231 over 10 trials, revealed significant performance differences among the hashing techniques.
Double hashing consistently produced the lowest average number of collisions.
Quadratic probing performed better than linear probing, but was not as efficient as double hashing.

This disparity in performance is due to a phenomenon called clustering.
Linear probing suffers from primary clustering, where collisions cause keys to form contiguous blocks, leading to longer and longer probe sequences.
Quadratic probing mitigates this by using a non-linear step size, but can still encounter secondary clustering for keys with the same initial hash value.
Double hashing is superior because it uses a second hash function to generate a unique step size for each key, effectively eliminating clustering and minimizing collisions.


// create find function to make sure its correct.

*/




#include "Double_Hash.h"
#include "Linear_Probe.h"
#include "QuadProbe.h"



int main() {

    srand(time(0));
    const int m = 1231;  // prime number
    const int n = 1000;  // number of insertions
    const int runs = 10; // number of tests

    double avgLinear = 0, avgQuadratic = 0, avgDouble = 0;

    for (int r = 0; r < runs; r++) {
        LinearHash lh(m);
        quadHash qh(m);
        doubleHash dh(m);

        for (int i = 0; i < n; i++) {
            unsigned long long key = ((unsigned long long)rand() << 32) | rand();
            lh.insert(key);
            qh.insert(key);
            dh.insert(key);
        }

        avgLinear += lh.getCollisions();
        avgQuadratic += qh.getCollisions();
        avgDouble += dh.getCollisions();
    }

    avgLinear /= runs;
    avgQuadratic /= runs;
    avgDouble /= runs;






    //my times were off so i had to reset it back to 0;
    avgLinear = 0;
    avgQuadratic = 0;
    avgDouble = 0;






    // corectness chec for find 

	cout << "Find func() test:\n";

	LinearHash lhTest(m);
	quadHash qhTest(m);
    doubleHash dhTest(m);

    unsigned long long testing[5] = { 111, 987654321, 55555, 20242024, 9999999999ULL };


    for (auto key: testing) {
        lhTest.insert(key);
        qhTest.insert(key);
		dhTest.insert(key);
    }

    bool correct = true;
    for (auto key:testing){
        if(!lhTest.find(key)|| !qhTest.find(key)||!dhTest.find(key)){
            correct = false;
		}
    }
    if (correct) {
        cout << "Find func worked" << endl;

    }
    else {
		cout << "Find func failed" << endl;
    }
    cout << "=============================================" << endl;




    cout << "\n\n";
    cout << "Run | Linear  | Quadratic |  Double\n";
    cout << "--------------------------------------\n";

    for (int r = 0; r < runs; r++) {
        LinearHash lh(m);
        quadHash qh(m);
        doubleHash dh(m);

        for (int i = 0; i < n; i++) {
            unsigned long long key = ((unsigned long long)rand() << 32) | rand();
            lh.insert(key);
            qh.insert(key);
            dh.insert(key);
        }

        int lc = lh.getCollisions();
        int qc = qh.getCollisions();
        int dc = dh.getCollisions();

        cout << r + 1 << "\t " << lc << "\t " << qc << "\t " << dc << endl;

        avgLinear += lc;
        avgQuadratic += qc;
        avgDouble += dc;
    }






    cout << "Average Collisions after 10 runs:\n";
    cout << "-----------------------------------------------\n";
    cout << "Linear Probing:    " << avgLinear/runs << endl; // forgot to put the di
    cout << "Quadratic Probing: " << avgQuadratic/runs << endl;
    cout << "Double Hashing:    " << avgDouble/runs << endl;






	return 0;
}
