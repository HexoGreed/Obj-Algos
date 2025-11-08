#pragma once
#include <iostream>     
#include <fstream>      
#include <string>       
#include <vector>       
#include <map>          
#include <set>          
#include <sstream>      // Lets us build a string of page numbers easily
#include <algorithm>    // Some useful helper functions
#include <cctype>       // For character functions, isalpha() and tolower()

// Making a type alias so I don't have to type this long thing out every time.

using InvertedIndex = std::map<std::string, std::set<int>>;

std::string LowerCaseWord(const std::string& word) {

    std::string LowerWord;


    for (char ch : word) {

        if (std::isalpha(ch)) { // Check if the character is a letter
            LowerWord += std::tolower(ch); // converts to lower
        }
    }

    return LowerWord;
}





///reads the  file and builds the inv index
InvertedIndex buildIndex(std::ifstream& inputFile, int wordsPerPage) {

	InvertedIndex THeindex;
    std::string currentWord;
    int wordCount = 0;
	int PageNumber = 1; // page 1

    //1 word at a time
    while ( inputFile >> currentWord) {

        wordCount++;

        PageNumber = ((wordCount-1) / wordsPerPage) + 1; // what page we're on

        std::string lowerWord = LowerCaseWord(currentWord); //to lower



        if(!lowerWord.empty()) { // only add non empty words
            THeindex[lowerWord].insert(PageNumber); // insert page number into the set for this word
		}
    }
	return THeindex;
}



//rtf file write 
void WriteTOFile(const InvertedIndex& index, const std::string& outputFilename) {
	std::ofstream outputFile(outputFilename);

	outputFile << "{\\rtf1\n"; // RTF header
	outputFile << "{//b Orwell 1984 Inverted Index}\n"; // Title bold


    char curentLetter = 0;
    for (const auto& pair : index) {
        const std::string& word = pair.first;
        const std::set<int>& pages = pair.second;


        if (word[0] != curentLetter) {
            curentLetter = word[0];
            outputFile << "\n{\\b " << char(toupper(curentLetter)) << "}\n"; // New letter header
        }

		outputFile << word << ": ";


        // Print the comma eparated page numbers w/o trailing comma
        bool firstPage = true;
        for (int page : pages) {
            if (!firstPage) {
                outputFile << ", "; // Add the comma before every page EXCEPT the first on
            }
            outputFile << page;
            firstPage = false;
        }


		outputFile << "\n"; // New line after each word entry
    }
}




void WordLookup(const InvertedIndex& index, const std::string& wordToFind) {


	std::string LowerWord = LowerCaseWord(wordToFind);
	auto it = index.find(LowerWord);



    std::cout << "word: \"" << wordToFind << std::endl;
    if (it != index.end()) {
		std::cout << "Found on pages: ";
		const auto& pages = it -> second;

		bool firstPage = true;
        for (int page : pages) {
            if (!firstPage) {
                std::cout << ", ";
            }
            std::cout << page;
			firstPage = false;
        }

		std::cout << std::endl;
        } else {
		std::cout << "Word not found" << std::endl;

    }


}