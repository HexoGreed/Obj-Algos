#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;


class doubleHash {
private:
	vector <unsigned long long> table;
	int m;
	int collisions;



public:
	doubleHash(int size) {
		m = size;
		table.assign(m, 0);
		collisions = 0;
	}


	int h1(unsigned long long key) {
		return key % m;
	}

	int h2(unsigned long long key) {
		return 1 + (key % (m - 1));
	}

	void insert(unsigned long long key) {
		int index = h1(key);
		int offset = h2(key);
		int i = 0;


		while (table[(index + i * offset) % m] != 0){
			collisions++;
			i++;
			if (i == m) 
				return ; // Table is full
		}
		table[(index + i * offset) % m] = key;



		
	}
	int getCollisions() {
		return collisions;
	}





	bool find(unsigned long long key) {
		int index = h1(key);
		int offset = h2(key);
		int i = 0;

		while (table[(index + i * offset) % m] != 0) {
			if (table[(index + i * offset) % m] == key) {
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

