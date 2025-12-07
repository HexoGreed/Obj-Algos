#pragma once
#include <iostream>
#include <vector>
#include <string>


using namespace std;




struct dataPair { // helps us store data
	string color;
	int rank;
};


///// binary max heap  (priority = rank)

class maxHeap {
private:
	vector <dataPair> Heap;

	void heapifyUp(int index) {
		if (index == 0) {
			return;
		} /// forgot to put this

		int parentIndex = (index - 1) / 2;


		if (Heap[index].rank > Heap[parentIndex].rank) {
			swap(Heap[index], Heap[parentIndex]);
			heapifyUp(parentIndex);
		}


	}


public:


	void insert(string x, int y) {
		Heap.push_back({ x,y });
		heapifyUp(Heap.size() - 1);
	}


	string search(int x) {
		for (int i = 0; i < Heap.size(); i++) {
			if (Heap[i].rank == x) {
				return Heap[i].color;
			}
		}

		return "Debug:: not found (search binary)\n";
	}

};








// Hash table ((size 11 linear probing)

class HashTable {
	private:
	
		struct Entry {
			dataPair data;
			bool taken = false;

		};

		Entry table[11];
		int size = 11;


		int hashFunction(string Key) {
			int sum = 0;
			
			for (char c : Key) {
				sum += int(c);
			}
			return sum % size;
		}



public:


	void insert(string x, int y) {
		int index = hashFunction(x);
		int startIndex = index;

		while (table[index].taken) {
			index = (index + 1) % size;
			if (index == startIndex) {
				return; // table full
			}
		}

		table[index].data = { x,y };
		table[index].taken = true;


	}

	int searchString(string s) {
		int index = hashFunction(s);
		int startIndex = index;




		while (table[index].taken) {

			if (table[index].data.color == s) {
				return table[index].data.rank;
			}


			index = (index + 1) % size;
			if (index == startIndex) {
				break;
			}
		}


		return -1;
	}
	
};




// binary Search tree (sort by color)

struct BstNode {
	dataPair data;
	BstNode* left = nullptr;
	BstNode* right = nullptr;

};

class BST {
private:

	BstNode* root = nullptr;


	BstNode* insertRec(BstNode* node, string x, int y) {
		if (node == nullptr) {
			BstNode* newNode = new BstNode;
			newNode->data = { x, y };
			return newNode;
		}

		if (x < node->data.color) {
			node->left = insertRec(node->left, x, y);


		} else if (x > node->data.color) {

			node->right = insertRec(node->right, x, y);
		}
		
		
		return node;
	}



	int searchRec(BstNode* node, string s) {
		
		if (node == nullptr) {
			return -1;
		}

		if (node->data.color == s) {
			return node->data.rank;
		}
		
		if (s < node->data.color) {
			return searchRec(node->left, s);


		}else {
			return searchRec(node->right, s);
		}
	}




public:


	void insert(string x, int y) {
		root = insertRec(root, x, y);

	}

	int search(string s) {
		return searchRec(root, s);
	}

};
