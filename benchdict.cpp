#include "util.hpp"
#include "DictionaryBST.hpp"
#include "DictionaryHashtable.hpp"
#include "DictionaryTrie.hpp"
using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

/* This file's purpose is the benchmark all of our data structures for
 * the completion of the speed of our Autocomplete. This includes a 
 * Binary Search Tree, a Hash Table and my own creation of a MultiwayTrie
 */
 
int main(int argc, char* argv[]) {

	string first_arge; // creates a string for all the command
			   // line arguments
	
	// argument count
	if (argc != 5)
		cout << "Invalid inputs given" << endl;
	
        std::vector<std::string> all_args;

        // what to do if there are actually arguments passed
        // this is done to concatonate strings
        if (argc > 1) {

    		first_arge = argv[1];

    		all_args.assign(argv + 1, argv + argc);
    	}

	char * pEnd; // used to parse the string of command line arguments
	int minSize; 
	int stepSize; // how much to increment in size from the dictionary
	int numIterations;
	ifstream in; // instream for the dict file
	long long totalTime;
	long long averageTime; 
	int counter = 0; // used to do numIterations
	Timer t1; // timer object

	in.open(argv[4]);

	minSize = strtol(argv[1],&pEnd,10); // parses the command line argument 
					    // to get the minSize from the 1st
					    // command line argument
	stepSize = strtol(argv[2],&pEnd,10); // " " 2nd command line argument
	numIterations = strtol(argv[3],&pEnd,10); // " " 3rd command line argument

	cout << "Benchmarking DictionaryBST" << endl;

	// does the loop operation numIterations times
	while ( counter < numIterations){

		DictionaryBST * bst = new DictionaryBST();
		Utils::load_dict (*bst,in,minSize + counter*stepSize); //loads the dictionary
		totalTime = 0; // sets totalTime to zero
		
		// inserts 10 gibberish words to 
		// get worst case scenarios for find them
		for (int i = 0; i != 100; i++){
			t1.begin_timer();

			bst->find("aaaaaaaaaaaaaaaa");
			bst->find("bbbbbbbbbbbbbbbb");
			bst->find("cccccccccccccccc");
			bst->find("dddddddddddddddd");
			bst->find("eeeeeeeeeeeeeeee");
			bst->find("ffffffffffffffff");
			bst->find("ggggggggggggggggg");
			bst->find("hhhhhhhhhhhhhhhhhhhh");
			bst->find("iiiiiiiiiiiiiiiiiiiii");
			bst->find("jjjjjjjjjjjjjjjjjjjj");

			totalTime += t1.end_timer(); // increments the totalTime taken
		}

		averageTime = totalTime / 100; // calculates the average time taken 
					       // to search for these 10 words
		
		
		cout << minSize + counter*stepSize << "\t" << averageTime << endl;
		

		counter++;
		delete bst;
	}

	counter = 0; // to reset
	totalTime = 0; // to reset
	cout << "Benchmarking DictionaryTrie" << endl;

	// does the loop operation numIterations times
	while ( counter < numIterations){

		DictionaryTrie * trie = new DictionaryTrie();
		Utils::load_dict (*trie,in,minSize + counter*stepSize); // loads the dictionary
		totalTime = 0;

		// inserts 10 gibberish words to 
		// get worst case scenarios for find them
		for (int i = 0; i != 100; i++){
			t1.begin_timer();

			trie->find("aaaaaaaaaaaaaaaa");
			trie->find("bbbbbbbbbbbbbbbb");
			trie->find("cccccccccccccccc");
			trie->find("dddddddddddddddd");
			trie->find("eeeeeeeeeeeeeeee");
			trie->find("ffffffffffffffff");
			trie->find("ggggggggggggggggg");
			trie->find("hhhhhhhhhhhhhhhhhhhh");
			trie->find("iiiiiiiiiiiiiiiiiiiii");
			trie->find("jjjjjjjjjjjjjjjjjjjj");

			totalTime += t1.end_timer();
		}

		averageTime = totalTime / 100; // calculates the average time taken 
					       // to search for these 10 words

		
		cout << minSize + counter*stepSize << "\t" << averageTime << endl;

		counter++;
		delete trie;
	}

	counter = 0;
	totalTime = 0;
	cout << "Benchmarking DictionaryHashtable" << endl;

	// does the loop operation numIterations times for benchmarking
	while ( counter < numIterations){

		DictionaryHashtable * ht = new DictionaryHashtable();
		Utils::load_dict (*ht,in,minSize + counter*stepSize); // loads the dictionary

		totalTime = 0;

		// inserts 10 gibberish words to 
		// get worst case scenarios for find them
		for (int i = 0; i != 100; i++){
			t1.begin_timer();

			ht->find("aaaaaaaaaaaaaaaa");
			ht->find("bbbbbbbbbbbbbbbb");
			ht->find("cccccccccccccccc");
			ht->find("dddddddddddddddd");
			ht->find("eeeeeeeeeeeeeeee");
			ht->find("ffffffffffffffff");
			ht->find("ggggggggggggggggg");
			ht->find("hhhhhhhhhhhhhhhhhhhh");
			ht->find("iiiiiiiiiiiiiiiiiiiii");
			ht->find("jjjjjjjjjjjjjjjjjjjj");

			totalTime += t1.end_timer();
		}

		averageTime = totalTime / 100; // calculates the average time
 
		cout << minSize + counter*stepSize << "\t" << averageTime << endl;
		
		counter++;
		delete ht;
	}

	in.close(); 

	return 0;
}


