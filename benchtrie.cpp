#include "util.hpp"
#include "DictionaryTrie.hpp"
#include <fstream>
#include <sstream>

void getResults(std::string dict_filename){
    std::ifstream in;
    in.open(dict_filename, std::ios::binary);

    std::cout << "\nLoading dictionary..." << std::endl;
    DictionaryTrie* dictionary_trie = new DictionaryTrie();

    Utils::load_dict(*dictionary_trie, in);

    std::cout << "Finished loading dictionary." << std::endl;
    std::cout << "\nStarting to time results" << std::endl;

    Timer T;
    std::vector<std::string> results;
    long long time_duration;

    // Test 1
    /**
    std::cout << "\n\tTest 1: prefix= \"*iterating through alphabet*\", num_completions= 10" << std::endl;
    T.begin_timer();
    int count = 0;
    results = dictionary_trie->predictCompletions("a",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("b",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("c",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("d",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("e",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("f",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("g",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("h",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("i",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("j",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("k",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("l",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("m",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("n",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("o",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("p",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("q",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("r",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("s",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("t",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("u",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("v",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("w",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("x",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("y",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("z",10);
    count += results.size();
    time_duration = T.end_timer();
    std::cout << "\tTest 1: time taken: " << time_duration << " nanoseconds." << std::endl;
    std::cout << "\tTest 1: results found: " <<  count << std::endl;

    // Test 2
    std::cout << "\n\tTest 2: prefix= \"a\", num_completions= 10" << std::endl;
    T.begin_timer();
    results = dictionary_trie->predictCompletions("a",10);
    time_duration = T.end_timer();
    std::cout << "\tTest 2: time taken: " << time_duration << " nanoseconds." << std::endl;
    std::cout << "\tTest 2: results found: " <<  results.size() << std::endl;

    // Test 3
    std::cout << "\n\tTest 3: prefix= \"the\", num_completions= 10" << std::endl;
    T.begin_timer();
    results = dictionary_trie->predictCompletions("the",10);
    time_duration = T.end_timer();
    std::cout << "\tTest 3: time taken: " << time_duration << " nanoseconds." << std::endl;
    std::cout << "\tTest 3: results found: " <<  results.size() << std::endl;

    std::cout << "\t";
    for (std::vector<std::string>::const_iterator i = results.begin(); i != results.end(); ++i)
        std::cout << *i << ' ';

    std::cout << std::endl;

    // Test 4
    std::cout << "\n\tTest 4: prefix= \"app\", num_completions= 10" << std::endl;
    T.begin_timer();
    results = dictionary_trie->predictCompletions("app",10);
    time_duration = T.end_timer();
    std::cout << "\tTest 4: time taken: " << time_duration << " nanoseconds." << std::endl;
    std::cout << "\tTest 4: results found: " <<  results.size() << std::endl;

    std::cout << "\t";
    for (std::vector<std::string>::const_iterator i = results.begin(); i != results.end(); ++i)
        std::cout << *i << ' ';

    std::cout << std::endl;

    // Test 5
    std::cout << "\n\tTest 5: prefix= \"man\", num_completions= 10" << std::endl;
    T.begin_timer();
    results = dictionary_trie->predictCompletions("man",10);
    time_duration = T.end_timer();
    std::cout << "\tTest 5: time taken: " << time_duration << " nanoseconds." << std::endl;
    std::cout << "\tTest 5: results found: " <<  results.size() << std::endl;
    

    std::cout << "\nWould you like to run additional tests? y/n\n";
    std::string response;
    std::getline(std::cin, response);
    

    if(response.compare("y") == 0){
    **/

    std::string prefix;
    std::string ws;
    int num_completions;

    std::cout << "\nAdditional user tests." << std::endl;
    std::cout << "Enter a prefix that you'd like to have a word predicted for: ";

    

    while(std::getline(std::cin, prefix)){
        if (prefix.compare("PLEASE EXIT") == 0)
            break;

        std::cout << "How many words predicted would you like? ";
        std::getline(std::cin, ws);
        num_completions = stoi(ws);

        int valid = 1;
        // returns an empty string if the prefix contains any non-alphabet/non-space chars
        for (char &c: prefix){
            if ((c !=  ' ') && !(isalpha(c))){
                std::cout << "Invalid Input! prefix cannot contain non-alphabets!" << std::endl;
                valid = 0;
                break;
            }
        }   

        if (valid == 1){
            std::cout << "\n\tThe prefix is \"" << prefix << "\", words requested = " << num_completions << std::endl;
            T.begin_timer();

            std::transform(prefix.begin(), prefix.end(), prefix.begin(),
            [](unsigned char c){ return std::tolower(c); });

            results = dictionary_trie->predictCompletions( prefix,num_completions);
            time_duration = T.end_timer();
            std::cout << "\tTime taken: " << time_duration << " nanoseconds." << std::endl;
            std::cout << "\tResults found: " <<  results.size() << "\n\n";
            
            std::cout << "You were most likely going to type: ";
            for (std::vector<std::string>::const_iterator i = results.begin(); i != results.end(); ++i)
                std::cout << *i << ' ';
        }
        std::cout << "\n\n";

        std::cout << "Type 'PLEASE EXIT' if you'd like to exit the application\n";      
        std::cout << "Enter a prefix that you'd like to have words predicted for: ";

    }

    delete dictionary_trie;
}

int main(int argc, char *argv[]) {
    if(argc < 2){
        std::cout << "Incorrect number of arguments." << std::endl;
        std::cout << "\t First argument: name of dictionary file." << std::endl;
        std::cout << std::endl;
        exit(-1);
    }

    getResults(argv[1]);
}
