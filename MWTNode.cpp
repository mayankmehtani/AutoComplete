#include "MWTNode.hpp"
#include<string>
using namespace std;

bool MWTNode::operator< (const MWTNode& other){

	// gives priority to those Nodes that have a
	// higher maxFreq
	if (maxFreq < other.maxFreq)
		return true;
	// handles a tie
	else if (maxFreq == other.maxFreq){
		// gives priority to Nodes which would be
		// found earlier in a physical dictionary

		if (nodeString < other.nodeString){
			return false;	
		}
		else{
			return true;
		}
	}

	return false; // gives other a higher priority
}
