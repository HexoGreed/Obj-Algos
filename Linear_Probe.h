#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;


class LinearHash {
private:
	vector<unsigned long long> table;
	int m;
	int collisions;



public:
	LinearHash(int size) {
		m = size;
		table.assign(m, 0);
		collisions = 0;
	}

	int hashFunc(unsigned long long key) {
		return key % m;
	}



	void insert(unsigned long long key) {
		int index = hashFunc(key);
		int start = index;
		while (table[index] != 0) {
			collisions++;
			index = (index + 1) % m;
			if (index == start) return;// table full


		}
		table[index] = key;


	}
	int getCollisions() { 
		return collisions;
	}




	bool find(unsigned long long key) {
		int index = hashFunc(key);
		int start = index;

		while (table[index] != 0) {
			if (table[index] == key) {
				return true; // Found it
			}

			index = (index + 1) % m;

			if (index == start) {
				return false;
			}
		}
		return false;
	}


};