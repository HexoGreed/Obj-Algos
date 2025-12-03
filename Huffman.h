#pragma once
#ifndef HUFFMAN_H
#define HUFFMAN_H


#include <iostream>
#include <vector>
#include <map>
#include <queue> // for priority q
#include <string>
using namespace std; // im not writing all those std::


struct Node { // for 1 node in tree
	char data; 
	int freq;
	Node* left, *right;

	Node(char data, int freq); // leaf node constuct (chars)

	Node(int freq, Node* left, Node* right); // internal nodes
};



//compare for the min heap
//orders by lowest freq

struct CompareNode{
	bool operator()(Node* a, Node* b);


};





/////////////////////////////////////////////////


string readFile(const string& filename); //read in file


map<char, int> getFreq(const string& text); // counts char frequency

Node* buldHUff(const map<char, int>& freqs); // builds tree using priority q




void generateCodes(Node* root, std::string code, std::map<char, std::string>& codes); // makes 0,1 codes



std::string decode(Node* root, const string& encodedText); // decodes


string encode(const string& text, const map<char, string>& codes); // encodes





double Print_calc(const map<char, string>& codes, const map <char, int>& freqs);

#endif // !HUFFMAN_H
