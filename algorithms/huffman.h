
//  Huffman.h
//  ec330_hw7
// Copyright Tiffany Lukmantara 2021 tiffaluk@bu.edu
// Copyright Thang Le 2021 thangle2@bu.edu

#ifndef Huffman_h
#define Huffman_h

#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <queue>

using namespace std;

class Node {
			public:
			char data;
			unsigned freq;
			bool isLeaf;
			Node* children[2];				// left and right child
			Node(char data, unsigned freq)
    		{
	        	this->data = data;
	        	this->freq = freq;
	        	isLeaf = false;
	        	for(int i=0; i<2; i++) {
						children[i] = NULL;			// set all children nodes to NULL first
				}
   			}
};

struct comparison									// custom comparator function to be used with min heap priority queue
{
    bool operator() (Node* left,Node* right)
    {
        return left->freq > right->freq;
    }
};

class Huffman {
	public:
		Node * root;
		priority_queue<Node *, vector<Node*>, comparison> Q; 		// min heap priority queue member used for generating the Huffman Tree

		Huffman(); 
		~Huffman();
		void buildHuffmanTree(char c_arr[], int i_arr[], int size);
		void printCodes();
		void decodeText(const char * c);

};


#endif /* Huffman_h */
