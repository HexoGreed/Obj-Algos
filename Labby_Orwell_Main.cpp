//Hamza s

#include "Inverted_Index.h"
#include <string>

using namespace std;

int main() {

	const string inputFilename = "Orwell 1984.txt";
	const string outputFilename = "Orwell1984_Index.rtf";

	const int wordsPerPage = 250; 

	ifstream inputFile(inputFilename);


	/*
	if (!inputFile.is_open()) {
		cout << "Cant open file '" << inputFilename << "'" << endl;
		return 1; 
	}
	DEBUGGING^^^

	it was annoying bc it wouldnt let me open the file 
	until I put the 1984.txt outside the files. weiiird

	*/ 



	cout << "Index '" << inputFilename << endl;
	InvertedIndex index = buildIndex(inputFile, wordsPerPage);
	inputFile.close();
	cout << "Index built. Found " << index.size() << " unique words " << endl;





	WriteTOFile(index, outputFilename);
	// lookup func tests
	cout << "Testing: " << endl;
	WordLookup(index, "winston");
	WordLookup(index, "ingsoc");
	WordLookup(index, "telescreen");
	WordLookup(index, "thoughtcrime");
	WordLookup(index, "computer");
	WordLookup(index, "Soulaboy"); //tell em (making sure not found)

	//

	return 0;

}