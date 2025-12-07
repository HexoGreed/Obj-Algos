#include "Heap_Hash_trees.h"
using namespace std;


int main() {
	maxHeap myHeap;
	HashTable myHash;
	BST myBst;



	vector<dataPair> inputs = {
	{"orange", 4}, {"blue", 7}, {"pink", 5}, {"black", 6}, {"green", 8},
		{"yellow", 1}, {"brown", 2}, {"red", 3}, {"purple", 10}, {"white", 9}
	};






	//load structs

	for (auto item : inputs) {
		myHeap.insert(item.color, item.rank);
		myHash.insert(item.color, item.rank);
		myBst.insert(item.color, item.rank);
	}




	cout << "Heap output: " << endl;
	cout << "Search Rank 5: " << myHeap.search(5) << endl;
	cout << "Search Rank 2: " << myHeap.search(2) << endl;
	cout << "Search Rank 11: " << myHeap.search(11) << endl;
	cout << endl;

	cout << "-------------------------------" << endl;


	cout << "Hasth table output: " << endl;
	cout << "Search 'pink': " << myHash.searchString("pink") << endl;
	cout << "Search 'green': " << myHash.searchString("green") << endl;
	cout << "Search 'grey': " << myHash.searchString("grey") << endl;
	cout << endl;
	cout << "-------------------------------" << endl;


	cout << "BST output: " << endl;
	cout << "Search 'white': " << myBst.search("white") << endl;
	cout << "Search 'black': " << myBst.search("black") << endl;
	cout << "Search 'violet': " << myBst.search("violet") << endl;


	return 0;

}