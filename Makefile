CC=g++
CXXFLAGS=-std=c++11 -g -Wall
LDFLAGS=-g

all: benchtrie util.o 

benchtrie: util.o DictionaryTrie.o 

DictionaryTrie.o: DictionaryTrie.hpp

util.o: util.hpp

clean:
	rm -f benchtrie *.o core* *~
