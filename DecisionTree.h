/*
 * DecisionTree.h
 *
 *  Created on: Jun 2, 2018
 *      Author: pigeon
 */

#ifndef DECISIONTREE_H_
#define DECISIONTREE_H_
#include <functional>
#include "BinaryTree.h"
#include <vector>
#include <set>
#include <math.h>
#include <ctime>
#include <cstdlib>
/*
 * This structure contains information in a node of Decision Tree
 * question it's a boolean lamda function that has a double argument that is a feature
 * prediction is the prediction made (it's -1 unless the node is a leaf)
 * featureAsked it's the index of the feature used in question
 * remaing_items and labes are used at train to find the question to separate data based on entropy
 * type is the type of the node ("node" or "leaf")
 * question_s it's the question in string format (e.g. ">=4")
 */
struct info{
	std::function<bool(double)> question;
	double prediction=-1;
	int featureAsked;
	std::vector<std::vector<double> > remaining_items;
	std::vector<double> labels;
	std::string tip,intrebare="no question";
};
class DecisionTree {
private:
	//tree it's the decision tree
	BinaryTree<info> tree;
	//a variable used to navigate and build the tree
	BinaryTree<info> curent;
	// calculate entropy for the root
	double Entropy(BinaryTree<info>);
	// calculate gain for a function
	double gain(std::function<bool(double)>);
	// make changes to the node to receive a question , or the label if it's a leaf
	void applyQuestion();
	// get a binary tree with a question (used to find the best question)
	BinaryTree<info> tryQuestion(std::function<bool(double)>);
	//train the DecisionTreee
	void train(BinaryTree<info>&);
	// find the best question
	void bestQuestion();
public:
	// constructor
	DecisionTree():tree{BinaryTree<info>()},curent{tree}{}
	//the fit function: used to train the tree
	void fit(std::vector<std::vector<double>>features ,std::vector<double>labels);
	//clasify a new dataset (argument: features)
	std::vector<double> predict(std::vector<std::vector<double> > features);
	//return the BinaryTree
	BinaryTree<info> Tree(){return tree;}
	//destructor
	virtual ~DecisionTree(){}
};

#endif /* DECISIONTREE_H_ */
