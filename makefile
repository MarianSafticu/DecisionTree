CXX=g++
CPPFLAGS=-std=c++17

all: main

main:
	$(CXX) $(CPPFLAGS) BinaryTree.h BinaryTree.cpp DecisionTree.h DecisionTree.cpp main.cpp -o executable 
	
clean:
	rm executable
