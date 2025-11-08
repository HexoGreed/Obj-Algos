#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;



class quadHash {
private:
	vector<unsigned long long> table;
	int m;
	int collisions;


public:

	quadHash(int size) {
		m = size;
		table.assign(m, 0);
		collisions = 0;
	}


	int hashFunc(unsigned long long key) {
		return key % m;
	}


	void insert(unsigned long long key) {
		int index = hashFunc(key);
		int i = 0;
		while (table[(index + i * i) % m] != 0) {
			collisions++;
			i++;
			if (i == m) return; // table full
		}
		table[(index + i * i) % m] = key;
	}

	int getCollisions() { 
		return collisions; 
	}


	bool find(unsigned long long key) {
		int index = hashFunc(key);
		int i = 0;

		while (table[(index + i * i) % m] != 0) {
			if (table[(index + i * i) % m] == key) {
				return true; // Found it
			}

			i++;

			if (i == m) {
				return false;
			}
		}

		return false;
	}



};