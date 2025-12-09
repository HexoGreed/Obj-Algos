/*
Hamza S













*/

















#include "Lab4_assignment2.h"
#include <iostream>

using namespace std;


int main() {


	cout << "part 1: " << endl;

	vector<string> binInput = {
		"10111101", "00000010", "10011011", "10111110", "01111111", "01010001",
		"10010110", "00001011", "11001111", "10011110", "11011011", "00101011",
		"01100001", "11110000", "01101111", "00000101", "01000101", "01000000"

	};

	extendHashTable ht1(4);

	for (const auto& s : binInput) {
		ht1.insert(stoi(s, nullptr, 2));
	}

	ht1.display();





	cout << "\npart 2: " << endl;

	vector<int> items_2 = { 16, 4, 6, 22, 24, 10, 31, 7, 9, 20, 26, 3, 1 };
	extendHashTable ht2(3);
	for (int item : items_2) {

		ht2.insert(item);
	}


	ht2.display();



	cout << "\n500 random ints: " << endl;

	auto runSim = [](int M, int N) {



		extendHashTable ht(M);
		random_device rd;
		mt19937_64 gen(rd());
		uniform_int_distribution<unsigned long long> dis; // Random 64-bit integers



		for (int i = 0; i < N; ++i) {
			// Masking to ensure it fits nicely in int for this 
			ht.insert(dis(gen) & 0x7FFFFFFF);
		}


		double expected = (double)N / M * log(2.0);



		cout << "Config M=" << M << ":" << endl;
		cout << "  Directory Size: " << ht.getDirSize() << endl;
		cout << "  Actual Leaves: " << ht.getLeafCount() << endl;
		cout << "  Expected Leaves: " << expected << endl;
		cout << "  Rehashes: " << ht.rehashCount << endl;
		};



	runSim(4, 500);
	runSim(8, 500);
	












	return 0;


}