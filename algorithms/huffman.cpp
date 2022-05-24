
// Copyright Tiffany Lukmantara 2021 tiffaluk@bu.edu
// Copyright Thang Le 2021 thangle2@bu.edu

#include "Huffman.h"

// Constructor
Huffman::Huffman() {
	this->root = NULL;
}

// Destructor
Huffman::~Huffman() {
}


// Constructs a Huffman Tree from the input
void Huffman::buildHuffmanTree(char c_arr[], int i_arr[], int size) {

	// inserting the characters into the min priority queue member based on their frequency
	for(int i=0; i < size; i++) {

		Node * curr = new Node(c_arr[i], i_arr[i]);
		Q.push(curr);
		curr->isLeaf = true;	// all nodes containing characters are the leaves of the Huffman tree
		
	}

	Node *min1, *min2, *root;
	// generating the Huffman Tree using the min priority queue member
	while (Q.size() > 1) {
		
        // Take lowest 2 frequency from top of min heap priority queue
        min1 = Q.top(); 		// lowest frequency
        Q.pop();				// remove lowest frequency from queue before getting second lowest

        min2 = Q.top(); 		// second lowest frequency
        Q.pop();				

        //Create a new root node with empty character and combined frequency of lowest 2
        root = new Node('\0', (min1->freq + min2->freq));

        root->children[0] = min1;	// assign lowest frequency as left child of root
        root->children[1] = min2;	// assign second lowest frequency as right child of root

 		//Push root into min heap priority queue
        Q.push(root);
    }

    this->root = Q.top();		// set root of Huffman tree to remaining element in the min heap priority queue

}

void print_subtree(Node * root, string code) {
	// helper function to go through the trees and encode each character
	int num;

	if(root == NULL) {
		return;
	}

	if(root->data == '\0') {							// not a leaf node

		print_subtree(root->children[0], code + '0');	// move down left child, append '0' to code
		print_subtree(root->children[1], code + '1');	// move down left child, append '1' to code

	} else {											// leaf node containing character is found

		num = 15-code.size();							// to count white spaces to print out
		cout << code << setw(num) << root->data << endl;
	}
}

// Prints the Huffman tree in a table format
void Huffman::printCodes() {
	cout << "Huffman Code Character " << endl;
	cout << "--------------------------" << endl;

	string code;
	print_subtree(this->root, code);
	cout << endl;

}

// Prints out the plain text, decoded version of the encoded text file
void Huffman::decodeText(const char * c) {
	ifstream file;
	string filename = c;	// encoded text file
	file.open(filename);

	char ch;

	Node* curr = this->root;

	if(curr == NULL) {	
		return;
	}

	cout << "The decoded text is: ";

	while(!file.eof() && file >> ch) {	// reading txt file char by char
		
		if(curr->isLeaf) {				// if leaf is found, that means a character is decoded
			cout << curr->data;
			curr = this->root;			// reset curr node to root node to traverse Huffman tree from top
		}

		if(ch == '0') {
			curr = curr->children[0];  // left child
		} else {
			curr = curr->children[1];  // right child
		}

	}

	if(curr->isLeaf) {
			cout << curr->data;			// accounting for last character
	}

	cout << endl;
	file.close();

}
