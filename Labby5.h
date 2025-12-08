#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <string>

using namespace std;


template <typename T>
struct SkipListNode {
	int key;
	T value;
	vector<SkipListNode<T>*> forward;

	SkipListNode(int k, T v, int lvl) : key(k), value(v), forward(lvl + 1, nullptr) {}
};



template< typename T>

class SkipList {
private:

	SkipListNode<T>* head;	
	int max_lvl;
	float prob;
	int level;


	int randomLvl() {
		int lvl = 0;

		while ((float)rand() / RAND_MAX < prob && lvl < max_lvl) {
			lvl++;
		}


		return lvl;
	}


public:



	SkipList(int maxLvl, float probability) : max_lvl(maxLvl), prob(probability), level(0) {

		head = new SkipListNode<T>(0, T(), max_lvl); // init head


	}


	~SkipList() {

		SkipListNode<T>* current = head;

		while (current != nullptr) {


			SkipListNode<T>* next = current->forward[0];

			delete current;

			current = next;
		}
	}




	/// ket search

	bool search(int key) {

		SkipListNode<T>* current = head;

		for (int i = level; i >= 0; i--) {


			while (current->forward[i] != nullptr && current->forward[i]->key < key) {
				current = current->forward[i];
			}
		}


		current = current->forward[0];
		return (current != nullptr && current->key == key);
	}



	void insert(int key, T vale) {
		vector<SkipListNode<T>*> update(max_lvl + 1);
		SkipListNode<T>* current = head;

		// 1. Find insert position
		for (int i = level; i >= 0; i--) {
			while (current->forward[i] != nullptr && current->forward[i]->key < key) {
				current = current->forward[i];
			}
			update[i] = current;
		}
		// NO BRACKET HERE! We are still in the function!

		// 2. Generate random level
		int new_level = randomLvl();

		if (new_level > level) {
			for (int i = level + 1; i <= new_level; i++) {
				update[i] = head;
			}
			level = new_level;
		}

		// 3. Link the new node
		SkipListNode<T>* newNode = new SkipListNode<T>(key, vale, new_level);
		for (int i = 0; i <= new_level; i++) {
			newNode->forward[i] = update[i]->forward[i];
			update[i]->forward[i] = newNode;
		}

	}



	//remove node by key

	bool remove(int key) {

		vector<SkipListNode<T>*> update(max_lvl + 1);
		SkipListNode<T>* current = head;



		for (int i = level; i >= 0; i--) {
			while (current->forward[i] != nullptr && current->forward[i]->key < key) {
				current = current->forward[i];
			}
			update[i] = current;
		}
		current = current->forward[0];

		if (current != nullptr && current->key == key) {
			for (int i = 0; i <= level; i++) {
				if (update[i]->forward[i] != current) {
					break;
				}
				update[i]->forward[i] = current->forward[i];
			}
			delete current;

			// Lower level if highest levels are now empty
			while (level > 0 && head->forward[level] == nullptr) {
				level--;
			}
			return true;
		}
		return false;


	}


	void display() {
		cout << "\nSkip List Contents:\n";


		for (int i = level; i >= 0; i--) {

			cout << "Level " << i << ": head -> ";

			SkipListNode<T>* node = head->forward[i];
			while (node != nullptr) {


				std::cout << node->key << " -> ";

				node = node->forward[i];
			}

			std::cout << "inf+\n"; // Displaying sentinel as requested
		}
		std::cout << "\n";
	}



};