#include "patriotAct.h"

using namespace std;


int main() {
	ifstream fin("PatriotAct.txt");
	
	if (!fin.is_open()) {
		cout << "DEBUG:: Cant open the file" << endl;
		return 1;
	}



	HashTable ht(1723);
	BST bst;



	string word;
	while (fin >> word) {
		word = cleanWord(word);
		if (word.empty()) continue;
		ht.insert(word);
		bst.insert(word);
	}
	fin.close();



	//build heap
	Heap heap;
	for (auto& entry : ht.table) {
		if (entry.occupied) {
			heap.insert(entry.word, entry.freq);
		}
	}



	//find most freq word

	auto start = high_resolution_clock::now();
	auto maxHeap = heap.getMax();
	auto end = high_resolution_clock::now();




	cout << "Heap: " << maxHeap.second << " (" << maxHeap.first << ") "
		<< "Time: " << duration_cast<microseconds>(end - start).count() << " us\n";



	// Hash Table

	start = high_resolution_clock::now();


	string maxWordHash = "";

	int maxFreqHash = -1;
	for (auto& entry : ht.table) {
		if (entry.occupied && entry.freq > maxFreqHash) {
			maxFreqHash = entry.freq;
			maxWordHash = entry.word;
		}


	}

	end = high_resolution_clock::now();
	cout << "Hash: " << maxWordHash << " (" << maxFreqHash << ") "
		<< "Time: " << duration_cast<microseconds>(end - start).count() << " us\n";


	


	//bst
	start = high_resolution_clock::now();
	auto maxBST = bst.findMaxFreq();
	end = high_resolution_clock::now();
	cout << "BST:  " << maxBST.second << " (" << maxBST.first << ") "
		<< "Time: " << duration_cast<microseconds>(end - start).count() << " us\n";




	cout << "\n Search Specific Words\n";
	vector<string> queries = { "terrorists", "the", "freedom" };

	for (auto& q : queries) {
		cout << "\n--- Searching for: " << q << " ---\n";

		// hash
		start = high_resolution_clock::now();
		int fHash = ht.search(q);
		end = high_resolution_clock::now();
		cout << "HASH TABLE Time: " << duration_cast<microseconds>(end - start).count() << " us (Freq: " << fHash << ")\n";


		// heap

		start = high_resolution_clock::now();
		int fHeap = heap.search(q);
		end = high_resolution_clock::now();
		cout << "HEAP Time: " << duration_cast<microseconds>(end - start).count() << " us (Freq: " << fHeap << ")\n";



		// Bst
		start = high_resolution_clock::now();
		int fBST = bst.search(q);
		end = high_resolution_clock::now();
		cout << "BST Time:   " << duration_cast<microseconds>(end - start).count() << " us (Freq: " << fBST << ")\n";
	}

	return 0;




	return 0;

}