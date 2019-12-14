# AutoComplete
AutoComplete is a software that predicts what word a user is trying to type out. The application uses a MultiWay Tree data structure to accomplish this. Our MultiWay Trie node component has 26 maps. Each of these maps represents an alphabet mapping to a pointer to another node in the tree (the pointers will help us traverse down the tree to insert new words and search through the tree later). Because we can traverse the tree through characters, each node in a way represents its own string that may be a word or may be a prefix to a word (e.g. "codi"). Each node component will keep a flag tracking if it does or does not represent a word.

We load the MultiWay Tree with a list of words along with their counts from a text (in this case unique_freq_dict.txt, but you can use any text file with a similar format to this file) and fill out the Tree with words from this list. Each node of the tree will have a frequency for itself. If the node happens to represent a word read in from the textfile it will have its frequency read in from the textfile. If it is not in the textfile it will stay at the default as it must be a prefix (i.e. 0). Each node will also store the highest frequency of all its descendents. To execute the program simply run make and then the benchtrie executable with the dictionary.

```sh
make
./benchdict unique_freq_dict.txt
```

The program will prompt the user to input a prefix and how many suggestions they would like returned. AutoComplete will first traverse down the tree to the given prefix. If the prefix does not exist (e.g. "yoiausdflkjhscviuhqkewrqsvx") zero suggestions will be returned. 

After traversing to the prefix in the tree, AutoComplete will run a breadth first search to return the number of completions the user requested. The priority queue in the breadth first search will manage priority for each Node using maximum frequency of descendents class variable. The program will stop if the number of predictions has been reached. If the priority queue is empty, then AutoComplete has completed traversing the entire tree and will return its predictions, even if the number of completions returned is lesser than the user had requested. 

