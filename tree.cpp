//shira yaish 327242939
//yael nave 213113889

#include <iostream>
#include <list>
#include <string>
#include "tree.h"
#include <algorithm>

using namespace std;

// Global counter for tree numbering
static int treeCounter = 1;

void Node::RemoveSonValue(string t)
{
	auto it = std::find_if(responses.begin(), responses.end(), [t](const Node* son) {
		return son->content == t;
		});

	if (it != responses.end()) {
		delete* it; // Delete the Node object to avoid memory leak
		responses.erase(it); // Remove the pointer from the list
	}
}

void Tree::deleteAllSubTree(Node* t)
{
	if (t == nullptr) {
		return;
	}

	for (auto& child : t->responses) {
		deleteAllSubTree(child);
	}

	delete t;
}

void Tree::addRoot(string val)
{
	
	if (root != nullptr) {
		deleteAllSubTree(root);
	}
	root = new Node(val);
}


Node* Tree::search(Node* p, string val, Node*& parent)//returning a pointer to the Node where this string is located.
{

	if (p == nullptr) {
		return nullptr;
	}

	if (p->content == val) {
		return p;
	}

	for (auto& child : p->responses) {
		parent = p; // Set parent before recursing
		Node* result = search(child, val, parent);
		if (result != nullptr) {
			return result;
		}
	}

	return nullptr;

}

void Tree::addson(string father, string son)
{
	Node* parent;
	Node* fatherNode = search(root, father, parent);
	if (fatherNode != nullptr) {
		Node* newSon = new Node(son);
		fatherNode->responses.push_back(newSon);
	}
}


void Tree::printTree(Node* r, int level)
{
	if (r == nullptr) {
		return;
	}

	for (int i = 0; i < level; ++i) {
		cout << "   ";
	}
	cout << r->content << endl;

	for (auto& child : r->responses) {
		printTree(child, level + 1);
	}
}

bool Tree::searchAndPrintPath(Node* p, string val)
{
	if (p == nullptr) {
		return false;
	}

	if (p->content == val) {
		cout << val << endl;
		return true;
	}

	for (auto& child : p->responses) {
		if (searchAndPrintPath(child, val)) {
			cout << "=>" << p->content;
			return true;
		}
	}

	return false;
}
bool Tree::printSubTree(Node* curr, string val)
{
	if (curr == nullptr) {
		return false;
	}

	if (curr->content == val) {
		printTree(curr);
		return true;
	}

	for (auto& child : curr->responses) {
		if (printSubTree(child, val)) {
			return true;
		}
	}

	return false;
}

bool Tree::addResponse(string root, string want, string com) {
	// First check if this is the correct tree (root matches)
	if (root == nullptr || root->content != rootVal) {
		return false;
	}

	Node* parent;
	Node* targetNode = search(root, want, parent);
	if (targetNode != nullptr) {
		Node* newResponse = new Node(com);
		targetNode->responses.push_back(newResponse);
		return true;
	}
	return false;
}

bool Tree::deleteSubTree(string val)
{
	Node* parent = nullptr;
	Node* toDelete = search(root, val, parent);

	if (toDelete == nullptr) {
		return false;
	}

	if (parent != nullptr) {
		parent->responses.remove(toDelete);
	}
	else {
		// Deleting the root, need to delete the entire tree
		deleteAllSubTree(root);
		root = nullptr;
	}

	deleteAllSubTree(toDelete);
	return true;
}


treeList::~treeList()
{
	for (auto tree : trees) {
		delete tree;
	}
	trees.clear();
}
void treeList::addNewTree(string val)
{
	Tree* newTree = new Tree();
	newTree->addRoot(val);
	trees.push_back(newTree);
}

void treeList::deleteTree(Tree* tree)
{
	trees.remove(tree);
	delete tree;
}
bool treeList::searchAndPrint(string s)
{
	
	bool found = false;
	for (auto tree : trees) {
		if (tree->searchAndPrintPath(s)) {
			found = true;
		}
	}

	if (!found) {
		cout << "ERROR" << endl;
		return false;
	}
	return true;
	

}
bool treeList::addResponse(string root, string want, string com)
{
	for (auto tree : trees) {
		if (tree->addResponse(root, want, com)) {
			return true;
		}
	}
	return false;

}
bool treeList::delResponse(string root, string want)
{
	for (auto tree : trees) {
		if (tree->getRoot() != nullptr && tree->getRoot()->content == root) {
			return tree->deleteSubTree(want);
		}
	}
	return false;

}
void treeList::printTree(string root)
{
	for (auto tree : trees) {
		if (tree->getRoot() != nullptr && tree->getRoot()->content == root) {
			tree->printAllTree();
			return;
		}
	}
}

void treeList::printSubTree(string treeName, string com)
{
	for (auto tree : trees) {
		if (tree->getRoot() != nullptr && tree->getRoot()->content == treeName) {
			if (tree->printSubTree(com)) {
				return;
			}
		}
	}
}

void treeList::printAllTrees()
{
	treeCounter = 1; // Reset counter
	for (auto tree : trees) {
		cout << "Tree #" << treeCounter++ << endl;
		tree->printTree(tree->getRoot());
	}
}