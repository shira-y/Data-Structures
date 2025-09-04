//shira yaish 327242939
//yael nave 213113889

#pragma once
#include <iostream>
#include <list>
#include <string>

using namespace std;

class Node //Node in the discussion tree,
{
public:
	string content;
	list <Node*> responses;
	Node(string con) {content = con;}
	friend class Tree;
};


class Tree //A discussion tree that have Node* root for the start of a discussion
{

	Node* root;
	Node* search(Node* p, string val, Node*& parent); //returns Node t where the string equals val. If t has a prent, the pointer parent will contain its address.
	bool searchAndPrintPath(Node* p, string val);
	void printTree(Node* r, int level = 0);
	bool printSubTree(Node* curr, string val);

public:

	Tree() { root = nullptr; }//empty tree
	~Tree() { deleteAllSubTree(root); }//tree distractor
	void deleteAllSubTree(Node* t);
	void addRoot(string val); //Building a root for a tree with a certain value
	void addson(string father,string son);
	bool search(string val)
	{
		Node* parent;
		return search(root, val, parent) != nullptr;
	}
	bool searchAndPrintPath(string val)
	{
		return searchAndPrintPath(root, val);
	}
	void printAllTree() {
		static int treeCounter = 1;
		cout << "Tree #" << treeCounter++ << endl;
		printTree(root);
	}
	void printSubTree(string val) { printSubTree(root, val); }
	bool printSubTree(Node* curr, string val) {
		if (printSubTree(root, val)) {
			Node* parent;
			Node* found = search(root, val, parent);
			if (found && parent) {
				cout << val << "=>" << parent->content << endl;
			}
			return true;
		}
		return false;
	}
	bool deleteSubTree(string val);
	Node* getRoot() { return root; }  // Added getRoot function
	bool addResponse(string root, string want, string com);  // Added addResponse function
	friend class treeList;

	
};




class treeList //Discussion list
{
	list<Tree*> trees;

public:
	treeList() {}
	~treeList();
	void addNewTree(string s);
	void deleteTree(Tree* );
	bool searchAndPrint(string s);
	bool addResponse(string root, string want, string com);
	bool delResponse(string root, string want);
	void printTree(string root);
	void printSubTree(string tree, string com);
	void printAllTrees();

};

