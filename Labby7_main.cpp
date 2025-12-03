
//Hamza S


#include "Huffman.h"
#include <iostream>
#include <iomanip>
#include <cmath> // log 2 and ceil
#include <fstream> // for ofstream



int main() {

    string text = readFile("huffman.in");
    if (text.empty()) {
        return 1;

        cout << "Dubugg: you forgot to put the file in [main]" << endl;
    }



    map<char, int> freqs = getFreq(text);
    Node* root = buldHUff(freqs);
    map<char, string> codes;



    generateCodes(root, "", codes);






    double totalCompressedBits = Print_calc(codes, freqs);
    cout << "debug::confrim trace code" << endl;





    int dsitSymbols = freqs.size();
    int bitsPerSymbol = ceil(log2(dsitSymbols));
    double totalUncompressedBits = text.length() * bitsPerSymbol;
    std::cout << "Total unencoded bits: " << totalUncompressedBits
    << " (" << text.length() << " chars * " << bitsPerSymbol << " bits/char)" << std::endl;





    double n = text.length();
    double h = 0.0;

    for (auto const& pair : freqs) {
        int freq = pair.second;
		double p = (double)freq / n;
		h -= p * log2(p);
    }


    double Th = h * n;
    double T_H_ceil = ceil(Th);
    double redundancy = totalCompressedBits - T_H_ceil;

    



    std::cout << "Entropy (H): " << std::fixed << std::setprecision(4) << h << " bits/symbol" << std::endl;
    std::cout << "Theoretical Lower Bound (T_H): " << Th << " bits" << std::endl;
    std::cout << "Actual Lower Bound [T_H]: " << T_H_ceil << " bits" << std::endl;
    std::cout << "Redundancy (T - [T_H]): " << redundancy << " bits" << std::endl;





    std::string encodedText = encode(text, codes);

    std::ofstream outFile("huffman.out");
    outFile << encodedText;
    outFile.close(); // forgot this lol

    cout << "\n\nHuffman.out is compressed" << endl;



    std::string encodedFromFile = readFile("huffman.out");
    std::string decodedText = decode(root, encodedFromFile);

    std::cout << "\nDecompressing huffman.out..." << std::endl;
    std::cout << "Original:   " << text << std::endl;
    std::cout << "Decoded:    " << decodedText << std::endl;

    if (text == decodedText) {
        std::cout << "\nText Matches." << std::endl;
    }
    else {
        std::cout << "Debug:: text isnt the same [main end]" << std::endl;
    }

    return 0;

}
