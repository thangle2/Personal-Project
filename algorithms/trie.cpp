include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

const int LETTERS = 52; // total number of letters when considering upper and lowercase

// create Node class to be used for Trie class
class Node {
		public:
			// char c;
			bool isWord;
			Node* children[LETTERS];

			Node() {
				isWord = false;


				for(int i=0; i<LETTERS; i++) {
					children[i] = NULL;			// set all children nodes to NULL first
				}


			}
};

// create Trie class
class Trie {
	private: 
		Node* root;

	public:
		Trie() {
			root = new Node();			// constructing Trie by allocating memory for root node
		}

		void insert(string word); 
		int search(string word);
	
};

// method to insert word to Trie
void Trie::insert(string word) {
	Node *curr = root;
	for(int i=0; i<word.size(); i++) {
		char c = word[i];
		int index = c - 'a';			// to find index of char from 0 to 52

		if(index < 0) {
				index = (c - 'A') + 26;
		}

		if(curr->children[index] == NULL) {
			curr->children[index] = new Node();		// allocate memory for new node if it doesnt exist in trie
		}
		curr = curr->children[index];
	}

	curr->isWord = true;				// after word is inserted, set boolean value isWord to true
}

// method to search whether a word is in the Trie
int Trie::search(string word) {
	// cout<<"Hello"<<endl;
			Node *curr = root;
			int count = 0;
			for(int i=0; i<word.size(); i++) {
				char c = word[i];
				int index = c - 'a';		// to find index of char from 0 to 52

				if(index < 0) {
						index = (c - 'A') + 26;
				}

				if(curr->isWord) {			// once a word is found, increment count
					count++;
				}
				if(curr->children[index] == NULL) {		// once reach a node without a child, return count
					return count;						
				}

				curr = curr->children[index];	// moving on to next level of children nodes
			}

			if (curr != NULL && curr->isWord) {
					count++;
			} 

	return count;		

}

// Determine the length of the longest word in the file
int fourA() {
	ifstream file;
	string longestword, filename = "BigData.txt";
	file.open(filename);

	char c;
	int maxlen = 0;

	while(!file.eof() && (file >> noskipws >> c)) {
		if(c != ' ' && c != '\n') {				// take every character in file other than ws or newline
			longestword += c;					// append to string
		} else {
			if(longestword.size() > maxlen){	// word is complete if ws or newline char is found
				maxlen = longestword.size();	// compare length of word to max length
			}
			longestword = "";					// clear string before checking next word
		}  	
		
	}

	if (longestword.size() > maxlen)			// handling last word in txt file
	{
		maxlen = longestword.size();
	}

	return maxlen;
}

// Determine rhe number of valid passwords in the file
int fourB() {
	ifstream file;
	string pw, filename = "BigData.txt";
	file.open(filename);

	char c;
	int valid_pw = 0;
	bool upper = false, lower = false, digit = false, len = false;

	while(!file.eof() && (file >> noskipws >> c)) { 	// read text file char by char without skipping white space
		// cout<< "inside while loop" <<endl;
		if(c != ' ' && c != '\n') {

			if (islower(c)) {
				lower = true; 	// to check if contains at least one lower case letter
			}

			if (isupper(c)) {
				upper = true;	// to check if contains at least one upper case letter 
			}

			if (isdigit(c)) {
				digit = true;	// to check if contains at least one digit
			}

			pw += c;		// append character to current string if not whitespace or newline char
		} else {

			len = (pw.size() >= 8 && pw.size() <= 20); //  check if between 8 and 20 characters in length

			if(lower && upper && digit && len){
				valid_pw++;		// update count if current string is a valid password
			}

			pw = ""; 			// clear string and reset all boolean values before checking next word
			upper = false;
			lower = false; 
			digit = false; 
			len = false;
		}
		  	
		
	}

	// checking if last word is valid password
	len = (pw.size() >= 8 && pw.size() <= 20); //  is between 8 and 20 characters in length

	if (lower && upper && digit && len)
	{
		valid_pw++;
	}

	return valid_pw;

}

// The number of English words (from the dictionary.txt file) that appear in the file
// which do not contain some combination of all the characters in candy abbreviation (lowercase or uppercase)
// {2, 3}: sour patch kids {s, p, k}
int fourC() { 
	ifstream file;
	string word, filename = "dictionary.txt";
	file.open(filename);
	
	Trie * mytrie = new Trie();			// create Trie for words in dictionary.txt
	while(getline(file, word)) {
		// filtering for candy abbreviation
		bool isValid = true;

		bool s = ((word.find('S') != string::npos) || (word.find('s') != string::npos));
		bool p = ((word.find('P') != string::npos) || (word.find('p') != string::npos));
		bool k = ((word.find('K') != string::npos) || (word.find('k') != string::npos));
		
		if (s && p && k)
		{
			isValid = false;

		}
		if(isValid) {
			mytrie->insert(word);		// insert word if does not contain some combination of candy abbreviation
		}
		
	}
	file.close();
	
	filename = "BigData.txt";
	file.open(filename);
	char c;
	string text;
	int count = 0;

	while(!file.eof() && (file >> noskipws >> c)) {
		if(isalpha(c)) {				// take only alphabet letters as dictionary contains only letters
			text += c;					// append to string if alphabet
		} else {
			for(int i=0; i<text.size(); i++) {				// once a non-alphabet char is found, word is complete
				string sub = text.substr(i,text.size()-i);	// searching for every substring of word in Trie
				count += mytrie->search(sub);				// keep adding to count of valid dictionary words
			}
		  	text = "";										// reset string before finding next word
		}
	}

	if (text.size() != 0)									// handling last word in text file
	{
		for(int i=0; i<text.size(); i++) {					// same as above for loop
				string sub = text.substr(i,text.size()-i);
				count += mytrie->search(sub);
		}
	}

	file.close();
	return count;
}
