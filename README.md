# AutoComplete
AutoComplete is a software that predicts what word a user is trying to type out. The application uses a [MultiWay Tree  data structure](https://en.wikipedia.org/wiki/M-ary_tree) to accomplish this. The MultiWay Tree Node component contains an array of 26 maps. Each map represents an alphabet mapping to a pointer to another node in our tree. This map of pointers allows us to traverse the Tree. Each Node in the tree will represent a string (either a prefix of a word or a word itself) through an instance variable. That string represents the sequence of characters that was used to get to the Node whle traversing the tree. We keep the string stored in each Node, and a flag denoting whether the string is a word (e.g. "coding") or just a prefix to an eventual word (e.g. "codi").

We load the MultiWay Tree with a list of words along with their frequency from a text file (in this case unique_freq_dict.txt, but you can use any text file with a similar format to this file) and fill out the Tree with words from this list and store the frequency of each word into their respective Node component's frequency variable. If a Node does not represent a word its frequency instance variable will stay at 0, denoting it as a prefix. During insertion, each Node will also have an instance variable that keeps track of the highest frequency of all its descendents.

To execute the application simply run make and then the benchtrie executable with the dictionary provided.

```sh
make
./benchtrie unique_freq_dict.txt
```

The program will then prompt the user to input a prefix and how many suggestions they would like to see. AutoComplete will first traverse down the tree to the given prefix. If the prefix does not exist in the tree (e.g. "yoiausdflkjhscviuhqkewrqsvx") zero suggestions are returned.

After traversing to the prefix in the tree, AutoComplete will run a breadth first search to return the number of completions the user requested. The priority queue in the breadth first search will manage the priority of the nodes prefering words with  larger values in the frequency of descendents instance variable. Thereby ensuring we always return the words with the highest frequencies first. The program will return our results if we have found the requested number of words or if the priority queue becomes empty. An empty priority queue signifies AutoComplete has completed traversing the entire tree for all the possible words from the user's prefix. You can see examples of the program running below.


![AutoComplete running](https://github.com/mayankmehtani/AutoComplete/blob/master/example.png)
