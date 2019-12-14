#ifndef DICTIONARY_TRIE_HPP
#define DICTIONARY_TRIE_HPP
//#include "MWTNode.hpp"
using namespace std; 
#include <string>
#include <unordered_map>
#include <vector>

/*
 * This file contains declerations for our MWTNode, MWTNodePtrComp
 * and our DictionaryTrie classes  
 */

// For our class to represent a Node for our MultiWay Trie
class MWTNode{

        friend class DictionaryTrie; // allows the DictionaryTrie to access MWTNode
   				     // member variables and functions

        friend class MWTNodePtrComp; // allows the MWTNodePtrComp to access MWTNode
				     // member variables and functions

private:
        unordered_map <char, MWTNode *>  alphabetArray; // a map linking each character
        bool isWord = false; // signifies whether this node marks the end of a word
        int freqs; // the frequency of this word in our dictionary
        int maxFreq = 0; // the max Frequency of this Node's  descendents
        string nodeString; // contains the string which we are representing
	void deleteAllMWTNodes(); // used for destroying the DictionaryTrie
	bool operator< (const MWTNode& other); // operator overload for '<' operator
};

// Comparator class so we can create a priority queue for the MultiWay Trie
class MWTNodePtrComp {

public:

	bool operator() (MWTNode*& lhs, MWTNode*& rhs) const {
		return *lhs < *rhs; // calls the '<' operations between the Nodes
	}

};

// DictionaryTrie class, this is a Multi-Way Trie where
// each Node will represent the entire alphabet and a ' ' char
class DictionaryTrie{

public:

	MWTNode * root = new MWTNode(); // root for our Tree
	
	int size; // number of Nodes in our Tree

	DictionaryTrie():size(0){}; // constructor

	~DictionaryTrie(); // destructor
	
	bool insert(string word, unsigned int freq); // inserts a word into our Dict 	

	bool find(string word) const; // search function for our Tree, to find a word

	// predicts what the most likely word to be typed will be given a 
	// certain prefix
	vector<string> predictCompletions(string prefix, unsigned int num_completions); 
	
};

#endif
