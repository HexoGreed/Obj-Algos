#include "Huffman.h"
#include <fstream>
#include <sstream>
#include <iomanip> // format table
#include <cmath> // log 2





Node::Node(char data, int freq) {
	this->data = data;
	this->freq = freq;
	left = right = nullptr;
}

Node::Node(int freq, Node* left, Node* right) {
	this->data = '\0'; // internals dont hold
	this->freq = freq;
	this->left = left;
	this->right = right;
}


bool CompareNode::operator()(Node* a, Node* b) {
	return a->freq > b->freq;
	//seeing if a is more freq than B

	//makes priority q min heap
}



//reads file into string
string readFile(const string& filename) {
	ifstream infile(filename);

	if (!infile.is_open()) {
		cout << "Debug:::: readfile cant open";
		return "";
	}


	stringstream buffer;
	buffer << infile.rdbuf();
	return buffer.str();
}





//counts char freq
map<char, int> getFreq(const string& text) {

	std::map<char, int> freqs;
	for (char c : text) {
		freqs[c]++;
	}

	return freqs;

}


//builds huff
Node* buldHUff(const map<char, int>& freqs) {
	priority_queue<Node*, vector<Node*>, CompareNode> pq;


	//had to do auto bc sometimes it wouldnt work for some reason idk whhy
	for (auto const& pair : freqs) {
		pq.push(new Node(pair.first, pair.second));
	}

	//loops until the root is the only thign
	while (pq.size() > 1) {
		Node* left = pq.top();
		pq.pop();
		Node* right = pq.top();
		pq.pop();


		Node* newNode = new Node(left->freq + right->freq, left, right);
		pq.push(newNode);
	}

	return pq.top();


}




void generateCodes(Node* root, string code, map<char, string>& codes) {

	if (root == nullptr) {
		return;
	} // basic check



	if (root->data != '\0') {
		codes[root->data] = code;
	}// checks if leaf node since they have chars



	generateCodes(root->left, code + "0", codes);
	generateCodes(root->right, code + "1", codes);

}





string decode(Node* root, const string& encodedText) {

	string decodedString = "";
	Node* curr = root;


	for (char bit : encodedText) {
		if (bit == '0') {
			curr = curr->left;
		}
		else {
			curr = curr->right;
		}




		//if we reach leaf node
		if (curr->left == nullptr && curr->right == nullptr) {

			decodedString += curr->data;
			curr = root; // go back to the root


		}
	}



	return decodedString;


}






double Print_calc(const std::map<char, std::string>& codes, const std::map<char, int>& freqs) {

	double totalBits = 0;
	int totalFreq = 0;

	cout << "HUffman table" << endl;
	cout << left
		<< std::setw(10) << "Symbol"
		<< std::setw(12) << "Code"
		<< std::setw(12) << "Freq"
		<< std::setw(12) << "Total Bits" << std::endl;
	cout << "------------------------------------" << endl;




	for (auto const& pair : freqs) {
		char symbol = pair.first;
		int freq = pair.second;

		string code = codes.at(symbol);
		int bits = freq * code.length();
		totalBits += bits;
		totalFreq += freq;


		string symbolStr = (symbol == ' ') ? "' '" : std::string(1, symbol); // using the conditional bc im not writing an else
		std::cout << std::left
			<< std::setw(10) << symbolStr
			<< std::setw(12) << code
			<< std::setw(12) << freq
			<< std::setw(12) << bits << std::endl;



	}

	cout << "----------------------" << endl;
	std::cout << std::left
		<< std::setw(10) << "Total"
		<< std::setw(12) << ""
		<< std::setw(12) << totalFreq
		<< std::setw(12) << totalBits << std::endl;

	return totalBits;

	}



string encode(const string& text, const map<char, string>& codes) {
	string encodedString = "";
	for (char c : text) {
		encodedString += codes.at(c);
	}
	return encodedString;
}


















