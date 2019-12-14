# AutoComplete
AutoComplete is a software that predicts what word a user is trying to type out. The application uses a MultiWay Tree data structure to accomplish this. Our MultiWay Trie node component has 26 maps. Each map represents an alphabet mapping to a pointer to another node in our tree (these pointers will help us traverse down the tree to insert new words and search through the tree later). Because we can traverse the tree through characters, during insertion each node will store a string of the word or prefix (e.g. "codi") it represents. Each node component will also keep a flag tracking if it does or does not represent a word.

We load the MultiWay Tree with a list of words along with their counts from a text (in this case unique_freq_dict.txt, but you can use any text file with a similar format to this file) and fill out the Tree with words from this list. Each node of the tree will have a frequency for itself. If the node happens to represent a word read in from the textfile it will have its frequency read in from the textfile. If it is not in the textfile it will stay at the default (i.e. 0) as it must be a prefix. Each node will also store the highest frequency of all its descendents. To execute the application simply run make and then the benchtrie executable with the dictionary provided.

```sh
make
./benchdict unique_freq_dict.txt
```

The program will prompt the user to input a prefix and how many suggestions they would like to see. AutoComplete will first traverse down the tree to the given prefix. If a prefix does not exist (e.g. "yoiausdflkjhscviuhqkewrqsvx") zero suggestions will be returned.

After traversing to the prefix in the tree, AutoComplete will run a breadth first search to return the number of completions the user requested. The priority queue in the breadth first search will manage priority for nodes using the maximum frequency of descendents variable. The program will return if the number of predictions has been reached or if the priority queue is empty. An empty priority queue signifies AutoComplete completed traversing the entire tree for the user's prefix and returned the maximum possible number of predictions from their prefix. You can see examples of the program running below.

![AutoComplete running](https://github.com/mayankmehtani/AutoComplete/blob/master/example.png)
