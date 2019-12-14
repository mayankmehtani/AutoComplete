# AutoComplete
AutoComplete is a software that predicts what word a user is trying to type out. The application uses a [MultiWay Tree  data structure](https://en.wikipedia.org/wiki/M-ary_tree) to accomplish this. The MultiWay Trie Node component contains an array of 26 maps. Each map represents an alphabet mapping to a pointer to another node in our tree, allowing us to traverse our Tree. Each Node represents a string (can be either a prefix of a word or the word itself), that was the series of characters used to get to the Node. We keep this string stored in each Node, and a flag denoting whether it is a word (e.g. "coding") or a prefix to an eventual word (e.g. "codi").

We load the MultiWay Tree with a list of words along with their frequency from a text file (in this case unique_freq_dict.txt, but you can use any text file with a similar format to this file) and fill out the Tree with words from this list. We store the frequency of each word into their respective Node component's frequency variable. If a Node does not represent a word its frequency class variable will stay at the default (i.e. 0), denoting it is a prefix. Each Node will also keep track of the highest frequency amongst all its descendents, which we set during insertion. 

To execute the application simply run make and then the benchtrie executable with the dictionary provided.

```sh
make
./benchtrie unique_freq_dict.txt
```

The program will prompt the user to input a prefix and how many suggestions they would like to see. AutoComplete will first traverse down the tree to the given prefix. If a prefix does not exist (e.g. "yoiausdflkjhscviuhqkewrqsvx") zero suggestions will be returned.

After traversing to the prefix in the tree, AutoComplete will run a breadth first search to return the number of completions the user requested. The priority queue in the breadth first search will manage the priority of the nodes using the maximum frequency of descendents variable, thereby ensuring we always return the words with the highest set frequency. The program will return our results if we find the requested number of words or if the priority queue becomes empty. An empty priority queue signifies AutoComplete has completed traversing the entire tree for all the possible words from the user's prefix. You can see examples of the program running below.


![AutoComplete running](https://github.com/mayankmehtani/AutoComplete/blob/master/example.png)
