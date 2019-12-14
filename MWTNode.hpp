#ifndef MWTNODE_HPP
#define MWTNODE_HPP

using namespace std;
#include <string>
#include <unordered_map>


class MWTNode{
	friend class DictionaryTrie; // allows the DictionaryTrie access to the MWTNode class

	friend class MWTNodePtrComp;

public:
	bool operator< (const MWTNode& other);

private:
	unordered_map <char, MWTNode *>  alphabetArray; // a map linking each character
	bool isWord = false; // signifies whether this node marks the end of a word
	int freqs; // the frequency of this word in our dictionary
	int maxFreq = 0; // the max Frequency of this Node's  descendents
	string nodeString;
};

#endif
