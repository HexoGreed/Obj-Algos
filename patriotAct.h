#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;


string cleanWord(string s){
	string cleaned = "";

	for (char c : s) {
		if (isalpha(c)) {  //checks if letter is alphabetic
			cleaned += tolower(c);
		}
	}
	

	return cleaned;

}




//hash table

struct hashEntry {
	string word;
	int freq;
	bool occupied;
	hashEntry() : word(""), freq(0), occupied(false) {}


};



struct HashTable {
	vector<hashEntry> table;

	int size;

	HashTable(int s) : size(s) {
		table.resize(size);
	}


	int hashFunc(const string& word) {
		unsigned long h = 0;
		for (char c : word) h = (h * 31 + c)%size;
		return h % size;
	}


	void insert(const string& word) {
		int index = hashFunc(word);
		int i = 0;

		while (true) {
			int probe = (index + i * i) % size;

			if (!table[probe].occupied) {
				table[probe].word = word;
				table[probe].freq = 1;
				table[probe].occupied = true;
				return;

			} else if (table[probe].word == word) {
				table[probe].freq++;
				return;
			}
			i++;
		}
	}

	int search(const string& word) {
		int index = hashFunc(word);
		int i = 0;
		while (true) {
			int probe = (index + i * i) % size;
			if (!table[probe].occupied) {
				cout << "DEBUG:: word not found "<< word << endl;
				return 0; 



			} else if (table[probe].word == word) {
				return table[probe].freq;
			}
		}

	}




};



//BST



struct BSTNode {
	string word;
	int freq;
	BSTNode* left, * right;
	BSTNode(string w) : word(w), freq(1), left(NULL), right(NULL) {}
};


struct BST {
	
	BSTNode* root = nullptr;

	BSTNode* insertRec(BSTNode* node, const string& word) {
		if (!node) {
			return new BSTNode(word);
		}
		if (word == node->word) {
			node->freq++;
		}
		else if (word < node->word) {
			node->left = insertRec(node->left, word);
		}
		else {
			node->right = insertRec(node->right, word);
		}
		return node;
	}



	void insert(const string& word) {
		root = insertRec(root, word);

	}


	int search(BSTNode* node, const string& word) {
		if (!node) {
			return -1;
		} 
		if (word == node->word) {
			return node->freq;
		}
		if (word < node->word) {
			return search(node->left, word);
		}

		return search(node->right, word);
	}

	int search(const string& word) {
		return search(root, word);
	}



	void findMaxFreqRec(BSTNode* node, pair<int, string>& maxPair) {
		if (!node) {
			return;
		}
		if (node->freq > maxPair.first) {
			maxPair = { node->freq, node->word };
		}

		findMaxFreqRec(node->left, maxPair);
		findMaxFreqRec(node->right, maxPair);
	}


	pair<int, string> findMaxFreq() {
		pair<int, string> maxP = { 0, "" };
		findMaxFreqRec(root, maxP);
		return maxP;
	}



};





//Heap


struct Heap {
	vector<pair<int, string>> arr; // (freq, word)

	void insert(const string& word, int freq) {
		arr.push_back({ freq, word });

		push_heap(arr.begin(), arr.end());
	}

	pair<int, string> getMax() {

		if (arr.empty()) return { 0, "" };

		return arr.front();
	}

	int search(const string& word) {

		for (auto& p : arr) {

			if (p.second == word) return p.first;
		}
		return 0;
	}

};