This is an implementation for Decision Tree classifier in C++

I try to compile on windows and does not work, firstly because of std::to_string() function
						secondly probably just mingw compiler 
So it works on linux, at least that's how i run it

It uses function for gain and entropy to select the questions for each node
( _It may be a little spageti, sorry for that :))_ )

The two main function are "train" and "fit"
the arguments must be 
	a vector of vectors of double for features
	a vector of doubles for labels

It uses a BinaryTree data structure that it's in BinaryTree.h

you could use the iterators for Binary Tree to see the  
