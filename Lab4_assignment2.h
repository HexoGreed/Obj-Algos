#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>
#include <string>
#include <bitset>
#include <memory>
#include <random>
using namespace std;


class leaf {
public:
	int depth;
	vector<int> items;
	set<int> referenceDirs; // tracks the mem indicies that point here


	leaf(int index, int i) {


		depth = i;
		referenceDirs.insert(index);

	}


	void insert(int item) {

		if (find(items.begin(), items.end(), item) == items.end()) {
			items.push_back(item);
			sort(items.begin(), items.end());
		}
	}


	//forgot to make this a func VVVV
	bool remove(int item) {
		auto it = find(items.begin(), items.end(), item);
		if (it != items.end()) {
			items.erase(it);
			return true;
		}
		return false;
	}



	bool is_full(size_t maxSize) const {

		return items.size() >= maxSize;

	}


	string toString() const {


		string s = "Depth: " + to_string(depth) + ", Refs: {";
		for (auto it = referenceDirs.begin(); it != referenceDirs.end(); ++it) {
			s += to_string(*it) + (next(it) != referenceDirs.end() ? "," : "");
		}

		s += "}, Items: [";
		for (size_t i = 0; i < items.size(); ++i) {

			s +=bitset<8>(items[i]).to_string() + " (" + to_string(items[i]) + ")";
			if (i < items.size() - 1) {
				s += ", ";
			}
		}


		s += "]";
		return s;
	}
};


class extendHashTable {


	private:

		int globalDepth;

		size_t maxBucketSize;


		//using sharedptr to deal with multiple indices pointing to the same leaf
		vector<shared_ptr<leaf>> directory;


	public:

		int rehashCount = 0;
		int DuplicateCount = 0;


		extendHashTable(size_t bucketSize) : globalDepth(1), maxBucketSize(bucketSize) {

			directory.push_back(make_shared<leaf>(0, 1));
			directory.push_back(make_shared<leaf>(1, 1));



		}


		int getDirIndex(int key) const {
			return key & ((1 << globalDepth) - 1);
		}


		int getDirSize() const {
			return directory.size();
		}


		int getLeafCount() const {
			set<leaf*> unique_leaves;

			for (const auto& leaf_ptr : directory) {

				unique_leaves.insert(leaf_ptr.get());
			}


			return unique_leaves.size();
		}


		void insert(int key) {
			int index = getDirIndex(key);
			auto currentLeaf = directory[index];

			// check duplicates
			if (find(currentLeaf->items.begin(), currentLeaf->items.end(), key) != currentLeaf->items.end()) {
				DuplicateCount++;
				return;
			}

			if (!currentLeaf->is_full(maxBucketSize)) {
				currentLeaf->insert(key);
			}
			else {
				currentLeaf->insert(key); // Temporarily add to redistribute
				split_leaf(index, currentLeaf);
			}
		}


		void split_leaf(int index, shared_ptr<leaf> leafPtr) {
			rehashCount++;

			if (leafPtr->depth == globalDepth) {
				double_directory();
			}

			int new_depth = leafPtr->depth + 1;



			// Create two new leaves
			auto leaf0 = make_shared<leaf>(index, new_depth);
			leaf0->referenceDirs.clear(); // FIX: Clear default ref

			auto leaf1 = make_shared<leaf>(index, new_depth);
			leaf1->referenceDirs.clear(); // FIX: Clear default ref





			// Re-distribute items
			int mask = 1 << (new_depth - 1);
			for (int item : leafPtr->items) {
				if (item & mask) leaf1->insert(item);
				else leaf0->insert(item);
			}



			// Update directory pointers
			for (size_t i = 0; i < directory.size(); ++i) {
				if (directory[i] == leafPtr) {
					if (i & mask) {
						directory[i] = leaf1;
						leaf1->referenceDirs.insert(i);
					}
					else {
						directory[i] = leaf0;
						leaf0->referenceDirs.insert(i);
					}
				}
			}
		}



		void double_directory() {


			size_t old_size = directory.size();

			for (size_t i = 0; i < old_size; ++i) {
				directory.push_back(directory[i]); // Duplicate pointer


				// Add the new alias index to the leafs reference list
				directory[i]->referenceDirs.insert(i + old_size);
			}
			globalDepth++;
		}

		void remove(int key) {


			int index = getDirIndex(key);
			if (directory[index]->remove(key)) {
				cout << "Removed " << key << endl;
			}
			else {
				cout << "DEBUG:: Key " << key << " not found" << endl;
			}
		}





		void display() {
			cout << "Global Depth: " << globalDepth << endl;
			set<leaf*> printed_leaves;
			for (size_t i = 0; i < directory.size(); ++i) {
				if (printed_leaves.find(directory[i].get()) == printed_leaves.end()) {
					cout << "Dir " << i << ": " << directory[i]->toString() << endl;
					printed_leaves.insert(directory[i].get());
				}
				else {
					cout << "Dir " << i << ": (Alias -> see Refs in other entries)" << endl;
				}
			}
		}
	};

