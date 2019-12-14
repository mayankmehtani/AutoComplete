#include "util.hpp"
#include "DictionaryTrie.hpp"
#include <queue>

/* operator overloading the '<' operator
 *  so we can do our comparisons between MWTNodes */
bool MWTNode::operator< (const MWTNode& other){

	// gives priority to those Nodes that have a
	// higher maxFreq
	if (freqs < other.freqs)
			return true;
	
	return false; // gives other a higher priority

}


/* Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string) */
bool DictionaryTrie::insert(std::string word, unsigned int freq)
{
	// check if we are trying to insert
	// an empty string into our dictionary
	if ( word.length() == 0){
		std::cout << "Empty Strings not Accepted." << std::endl;
		return false;
	}
	
	// check for if the word already exists in the 
	// dictionary tree
	if ( find(word) ){
		std::cout << "This word is already in our Dictionary." << std::endl;
		return false;
	}	

	MWTNode * working = root; // sets working to the root so we can 
	unordered_map<char,MWTNode *>::iterator finder; //finds Node we want from our map 
  
	string currentString  = "";

	// iterates through the word
	// and creates a new Trie for each letter
	for (char &c : word ){
		currentString.append(1,c);		

		finder = working -> alphabetArray.find(c);		

		// changes the maxFreq of the node we are
		// currently on while traversing down if it is smaller than 
		// the new one
		if (working -> maxFreq < (int) freq){
			working -> maxFreq = freq;
		}

		// traverses down the pre-existing path
		if ( finder != (working -> alphabetArray.end()) ) {
			working = finder->second; // sets working to the ptr to that keyvalue
		}
		// What to do if that path has not been created yet
		else {
			MWTNode * toInsert = new MWTNode();	// creates the new path
			working -> alphabetArray.insert({c,toInsert}); // new Dict entry
			working = toInsert; // sets working to the new Dict entry
			working -> nodeString = currentString;
		}

	
	}

	working -> isWord = true; // changes the isWord flag to true for Working
	working -> freqs = freq; // sets the frequencies to the user input freq	
	size++;	

	return true;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const
{
    
	unordered_map<char,MWTNode * >::iterator existFind; // used to determine if a node is there  
	MWTNode * working = root; // sets working to root, as we need to start there for traversals

	// Traversal through the word, character by character 
	// so we can find it in the dictionary
	for (char &c: word) {
	
		existFind = working -> alphabetArray.find(c); // gets the iterator associated with c

		// if the iterator contains a null ptr then
		// we can return false as the word searched does not 
		// exist in our dictionary
		if ( existFind == working -> alphabetArray.end() )
			return false; 
	
		working = existFind -> second; // working is the pointer associated with 
					       // iterator existFind (a non-null pointer)
  	}	
	
	// makes sure this insertion was a word
	if ( working -> isWord )  
  		return true;

	return false;
}

/* Return up to num_completions of the most frequent completions
 * of the prefix, such that the completions are words in the dictionary.
 * These completions should be listed from most frequent to least.
 * If there are fewer than num_completions legal completions, this
 * function returns a vector with as many completions as possible.
 * If no completions exist, then the function returns a vector of size 0.
 * The prefix itself might be included in the returned words if the prefix
 * is a word (and is among the num_completions most frequent completions
 * of said prefix)
 */
std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix, unsigned int num_completions)
{
	std::vector<std::string> words;

	// returns an empty vector if num_completions is negative or zero
	if ( (!(num_completions > 0))){
	std::cout << "Invalid Input! num_completions must be positive!"  << std::endl;	
	return words;
	}

	// returns an empty vector if the prefix is a blank string
	if ( (prefix.length() == 0)){
	std::cout << "Invalid Input! prefix cannot be an empty string!" << std::endl;
	return words;
	}

	// returns an empty string if the prefix contains any non-alphabet/non-space chars
	for (char &c: prefix){
	// check for if it is not a space and not an alphabet
	if ( (c !=  ' ') && (!(isalpha(c))) ){
				std::cout << "Invalid Input! prefix cannot contain non-alphabets!" << std::endl;
		return words;
		}
	}


	MWTNode * working = root; // sets working to root, so we can begin our Traversal downwards
	unordered_map<char,MWTNode * >::iterator existFind; // declares the iterator to see if the char exists
														// in a certain map   

	// traverses through to the 'prefix' string
	for (char &c: prefix) {
		existFind = working -> alphabetArray.find(c); // sets the iterator to the pair associated 
													  // with curent character wea are traversing in prefix

		// returns an empty string if this prefix is not there in the dictionary
		// as existFind contains a null pointer
		if ( existFind == working -> alphabetArray.end() )
			return words;

		working = existFind -> second;	// sets working to the ptr associated with this char
										// to help us traverse down
	}


	std::priority_queue < MWTNode *, vector <MWTNode *>, MWTNodePtrComp > q1; //  a priority queue
	std::priority_queue < MWTNode *, vector <MWTNode *>, MWTNodePtrComp > q2; // a priority queue for all the words
																			  // we will find


	q1.push(working); // pushes the prefix Node to our priority queue

	// push the prefix to the priority queue only if it is a word
	if (working -> isWord) 
		q2.push(working);

	
	while ( !q1.empty() ){

		working = q1.top(); // sets working to the Node with the highest Frequence
		q1.pop(); // pops the Node with the highest Frequency so we can push the Nodes in 
				// with descending order now

		// iterates through working pushing all its children in
		// and will push in to the wordsQueue if it passes the isWord boolean
		for (auto it = working -> alphabetArray.begin(); it != working -> alphabetArray.end(); ++it){

			q1.push(it -> second);

			if (it -> second -> isWord)
				q2.push(it -> second);

		}

	}

	int numWords; 

	// checks whether we need to return num_completions
	// or if there are less than num_completions 
	// how many nodes to pop off
	if ( num_completions <  q2.size() )
	    numWords = num_completions;
	else
	    numWords = q2.size();

	unsigned int counter = 0; // a counter for how many words we have pushed in
	unsigned int numWords1 =  numWords; 

	// a while loop to push those words into
	// the return vector of Strings
	while (counter != numWords1){

	working = q2.top();
	q2.pop();

	words.push_back(working -> nodeString);
	++counter;

	}

	return words;

}

/* extension of our Destructor destroy all the Nodes
 * in our Dictionary Trie */
void MWTNode::deleteAllMWTNodes(){

	MWTNode * working; // a pointer to a MWTNode, which we will use for
			   // traversing the tree

	// makes continuous recursive calls until we get to a leaf node
	// and then begins popping off the stack
	for (auto it = alphabetArray.begin(); it != alphabetArray.end(); ++it){
		working = (*it).second; 
		working -> deleteAllMWTNodes();		
	}
	
	delete this; // deletes the calling object
}


/* Destructor */
DictionaryTrie::~DictionaryTrie(){
	
	// calls deleteAllMWTNodes which deletes all Nodes in
	// our Tree
	root -> deleteAllMWTNodes();

}
