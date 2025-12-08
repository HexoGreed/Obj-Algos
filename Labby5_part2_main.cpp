/*
Hamza S

QA:



1. Is it important to know the expected size of the skip list? Why? 
	
	Yes knowing the expected size allows you to select the optimal max_level for the data struct.

	if the max level is too low for the data the list essentially becomes a regular linked list
	making the performace worse from O(log N) to O(N). if its too high you have wasted memory.




2. How can we calculate the max level used for a skip list? Why?
	
	The maximum level is calculated using the log of the expected 
	num of elements based on prob.
	
	L = log base( (1/p)) * (N).
	if(p = 0.5, this is L = log base(2) * (N)

	this calculation ensures that the num of nodes at the highest lvl is small 
	keeping a pyramid stucture 


3. Is the random generator used suitable for determining the random level used for an
insertion? Can we find a better option? The answer will be related to the random library
used.


no the rand() func is not suitable for very high performance structures.
Its an older generator/function meaning it has poor distrubution and isnt truely random
so it can repeat patterns.

A better option is in the <random> lib, specifically the Mersenne Twister engine (std::mt19937)
better distrubution so the skip list is more balanced. But if we're going for true randomness then no,
no random generator other than user input would work.




4. Why would using a skip list be a bad idea if duplicate keys were allowed?


If multiple nodes share the same key the remove() func becomes confused and doesnt know what to delete. Also 
searching for a specific duplicate key would force the algo to go through all duplicates 
making the time complexity go toward O(N)












*/



















#include "Labby5.h"
#include <iostream>
#include <chrono>
using namespace std;

int main() {
	srand(time(0)); 

	SkipList<string> skipList(6, 0.5);

	cout << "Inseritng 10 random nums " << endl;


	for (int i = 1; i <= 10; ++i) {
		int key = rand() % 2000 + 1; // rnadge from 1-2000

		skipList.insert(key, "value" + to_string(i));
	}
	skipList.insert(100, "targetValue");


	skipList.display();


	cout << "searching: " << endl;

	int searchKey = 100; // example

	if (skipList.search(searchKey)) {
		cout << "Key " << searchKey << " found" << endl;



	}else {
		cout << "DEBUG::  " << searchKey << "not found" << endl;

	}

	skipList.display();







	cout << "\n Removing key: " << searchKey << endl;

	if (skipList.remove(searchKey)) {

		cout << "Key " << searchKey << " removed." << endl;

	}else {
		cout << "Debug::  " << searchKey << " not found." << endl;
	}

	// Display again to verify removal
	skipList.display();













	return 0;
	
}
