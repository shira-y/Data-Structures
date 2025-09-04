#pragma once
#include<iostream>
#include "LibraryDataStructure.h"
using namespace std;

template<class T>
class BTree : public LibraryDataStructure<T>
{
private:
	class BNode
	{
	public:
		int m;		//max num of records in node +1
		T* records;
		BNode** sons;
		BNode* parent;
		int numOfRecords;
		int numOfSons;
		BNode(int _m);
		~BNode();
		bool isLeaf();
		void insert(T record);
		void remove(T record);
		void printKeys();
		void merge(int idx);
		void fill(int idx);
		void borrowFromNext(int idx);
		void borrowFromPrev(int idx);
		T findPredecessor(int idx);
		T findSuccessor(int idx);
	};
	int m;
	BNode* root;

	void clear(BNode* current);
	void inorder(BNode* current);
	BNode* findAddNode(BNode* current, T record);
	void split(BNode* current);
	T* search(BNode* current, int key, int& counter);
public:
	BTree(int degree);
	~BTree();
	void inorder();
	void insert(T record);
	T* search(int key);
};

////////////////////////////////////////////////////////////////

template<class T>
BTree<T>::BNode::BNode(int _m) : m(_m), records(new T[m - 1]), sons(new BNode* [m]), parent(nullptr), numOfRecords(0), numOfSons(0) {}

template<class T>
BTree<T>::BNode::~BNode()
{
	delete[] records;
	delete[] sons;
}

template<class T>
bool BTree<T>::BNode::isLeaf()
{
	return numOfSons == 0;
}

template<class T>
void BTree<T>::BNode::insert(T record)
{
	// Early exit if node is full, should be handled by caller
	if (numOfRecords == m - 1) return;

	// Find the position to insert the new record
	int i = numOfRecords - 1;
	while (i >= 0 && records[i].getKey() > record.getKey()) {
		records[i + 1] = records[i];
		i--;
	}

	// Insert the new record
	records[i + 1] = record;
	numOfRecords++;
}

template<class T>
void BTree<T>::BNode::remove(T record) {
	int i = 0;
	while (i < numOfRecords && records[i].getKey() < record.getKey()) {
		i++;
	}

	if (i < numOfRecords && records[i] == record) {
		// The record is found in the current node
		if (isLeaf()) {
			// Case 1: The node is a leaf
			for (int j = i + 1; j < numOfRecords; j++) {
				records[j - 1] = records[j];
			}
			numOfRecords--;
		}
		else {
			// Case 2: The node is not a leaf
			// A) The left child has at least t keys
			if (sons[i]->numOfRecords >= (m + 1) / 2) {
				T pred = findPredecessor(i);
				records[i] = pred;
				sons[i]->remove(pred);
			}
			// B) The right child has at least t keys
			else if (sons[i + 1]->numOfRecords >= (m + 1) / 2) {
				T succ = findSuccessor(i);
				records[i] = succ;
				sons[i + 1]->remove(succ);
			}
			// C) Both children have t-1 keys, merge them
			else {
				merge(i);
				sons[i]->remove(record);
			}
		}
	}
	else if (!isLeaf()) {
		// The key is not present in this node and this node is not a leaf
		bool flag = (i == numOfRecords);

		// Before going down, ensure that the child has at least t keys
		if (sons[i]->numOfRecords < (m + 1) / 2) {
			fill(i);
		}

		// The last child has been merged with its sibling
		if (flag && i > numOfRecords) {
			sons[i - 1]->remove(record);
		}
		else {
			sons[i]->remove(record);
		}
	}
	// If key is not found and this is a leaf, do nothing
}

template<class T>
T BTree<T>::BNode::findPredecessor(int idx) {
	BNode* current = sons[idx];
	while (!current->isLeaf()) {
		current = current->sons[current->numOfSons - 1];
	}
	return current->records[current->numOfRecords - 1];
}

template<class T>
T BTree<T>::BNode::findSuccessor(int idx) {
	BNode* current = sons[idx + 1];
	while (!current->isLeaf()) {
		current = current->sons[0];
	}
	return current->records[0];
}

template<class T>
void BTree<T>::BNode::fill(int idx) {
	// If the previous child has more than t-1 keys, borrow from it
	if (idx != 0 && sons[idx - 1]->numOfRecords >= (m + 1) / 2) {
		borrowFromPrev(idx);
	}
	// If the next child has more than t-1 keys, borrow from it
	else if (idx != numOfSons - 1 && sons[idx + 1]->numOfRecords >= (m + 1) / 2) {
		borrowFromNext(idx);
	}
	// Merge this child with its sibling
	else {
		if (idx != numOfSons - 1) {
			merge(idx);
		}
		else {
			merge(idx - 1);
		}
	}
}

template<class T>
void BTree<T>::BNode::borrowFromPrev(int idx) {
	BNode* child = sons[idx];
	BNode* sibling = sons[idx - 1];

	// Moving all keys in child one step ahead
	for (int i = child->numOfRecords - 1; i >= 0; --i) {
		child->records[i + 1] = child->records[i];
	}

	// If not a leaf, move all its child pointers one step ahead
	if (!child->isLeaf()) {
		for (int i = child->numOfRecords; i >= 0; --i) {
			child->sons[i + 1] = child->sons[i];
		}
		// Move sibling's last child as child's first child
		child->sons[0] = sibling->sons[sibling->numOfSons - 1];
		if (child->sons[0] != nullptr) {
			child->sons[0]->parent = child;
		}
		sibling->numOfSons--;
		child->numOfSons++;
	}

	// Setting child's first key equal to records[idx-1] from the current node
	child->records[0] = records[idx - 1];

	// Moving the key from the sibling to the parent
	records[idx - 1] = sibling->records[sibling->numOfRecords - 1];

	child->numOfRecords += 1;
	sibling->numOfRecords -= 1;
}

template<class T>
void BTree<T>::BNode::borrowFromNext(int idx) {
	BNode* child = sons[idx];
	BNode* sibling = sons[idx + 1];

	// records[idx] is inserted as the last key in child
	child->records[child->numOfRecords] = records[idx];

	// Sibling's first child is inserted as the last child into child
	if (!child->isLeaf()) {
		child->sons[child->numOfRecords + 1] = sibling->sons[0];
		if (sibling->sons[0] != nullptr) {
			sibling->sons[0]->parent = child;
		}
		child->numOfSons++;
	}

	// The first key from sibling is inserted into records[idx]
	records[idx] = sibling->records[0];

	// Moving all keys in sibling one step behind
	for (int i = 1; i < sibling->numOfRecords; ++i) {
		sibling->records[i - 1] = sibling->records[i];
	}

	// Moving the child pointers one step behind if it's not a leaf
	if (!sibling->isLeaf()) {
		for (int i = 1; i <= sibling->numOfSons - 1; ++i) {
			sibling->sons[i - 1] = sibling->sons[i];
		}
		sibling->numOfSons--;
	}

	child->numOfRecords += 1;
	sibling->numOfRecords -= 1;
}

template<class T>
void BTree<T>::BNode::merge(int idx) {
	BNode* child = sons[idx];
	BNode* sibling = sons[idx + 1];

	// Pulling a key from the current node and inserting it into the correct position of child
	child->records[child->numOfRecords] = records[idx];
	child->numOfRecords++;

	// Copying the keys from sibling to child at the end
	for (int i = 0; i < sibling->numOfRecords; ++i) {
		child->records[child->numOfRecords + i] = sibling->records[i];
	}
	child->numOfRecords += sibling->numOfRecords;

	// Copying the child pointers from sibling to child
	if (!child->isLeaf()) {
		for (int i = 0; i <= sibling->numOfSons - 1; ++i) {
			child->sons[child->numOfSons + i] = sibling->sons[i];
			if (sibling->sons[i] != nullptr) {
				sibling->sons[i]->parent = child;
			}
		}
		child->numOfSons += sibling->numOfSons;
	}

	// Moving all keys after idx in the current node one step before
	for (int i = idx + 1; i < numOfRecords; ++i) {
		records[i - 1] = records[i];
	}

	// Moving the child pointers after (idx+1) in the current node one step before
	for (int i = idx + 2; i <= numOfSons - 1; ++i) {
		sons[i - 1] = sons[i];
	}

	numOfRecords--;
	numOfSons--;

	// Finally, delete the sibling node
	delete sibling;
}

template<class T>
void BTree<T>::BNode::printKeys()
{
	cout << '(';
	if (numOfRecords > 0) {
		for (int i = 0; i < numOfRecords - 1; i++)
			cout << records[i].getKey() << ",";
		cout << records[numOfRecords - 1].getKey();
	}
	cout << ')' << endl;
}

template<class T>
BTree<T>::BTree(int degree) : m(degree), root(nullptr)
{}

template<class T>
BTree<T>::~BTree()
{
	clear(root);
}

template<class T>
void BTree<T>::inorder()
{
	inorder(root);
}

template<class T>
void BTree<T>::insert(T record)
{
	if (root == nullptr) {
		root = new BNode(m);
		root->records[0] = record;
		root->numOfRecords = 1;
	}
	else {
		BNode* leaf = findAddNode(root, record);
		leaf->insert(record);
		if (leaf->numOfRecords == m) {
			split(leaf);
		}
	}
}

//private recursive helper functions
template<class T>
void BTree<T>::clear(BNode* current)
{
	if (current == nullptr)
		return;

	for (int i = 0; i < current->numOfSons; ++i)
		clear(current->sons[i]);

	delete current;
}

template<class T>
void BTree<T>::inorder(BNode* current)
{
	if (current == nullptr)
		return;

	int i;
	for (i = 0; i < current->numOfSons && i < current->numOfRecords; i++) {
		inorder(current->sons[i]);
		// Print the key after visiting left subtree
		if (i < current->numOfRecords) {
			current->printKeys();
		}
	}

	// Visit the last child if it exists
	if (i < current->numOfSons) {
		inorder(current->sons[i]);
	}

	// If this is a leaf, print its keys
	if (current->isLeaf()) {
		current->printKeys();
	}
}

template<class T>
typename BTree<T>::BNode* BTree<T>::findAddNode(BNode* current, T record)
{
	// Base case: If current node is a leaf node, return it
	if (current->isLeaf()) {
		return current;
	}

	// Find the child to traverse to
	int i = 0;
	while (i < current->numOfRecords && record.getKey() > current->records[i].getKey()) {
		i++;
	}

	// Recurse to the appropriate child
	return findAddNode(current->sons[i], record);
}

template <class T>
void BTree<T>::split(BNode* current)
{
	int splitIndex = (m - 1) / 2; // Middle index
	T middleRecord = current->records[splitIndex];

	// Create new node for the second half
	BNode* newNode = new BNode(m);
	newNode->parent = current->parent;

	// Move second half of records to the new node
	int j = 0;
	for (int i = splitIndex + 1; i < current->numOfRecords; i++) {
		newNode->records[j] = current->records[i];
		j++;
		newNode->numOfRecords++;
	}

	// Update current node's record count
	current->numOfRecords = splitIndex;

	// If not a leaf, also move the children
	if (!current->isLeaf()) {
		j = 0;
		for (int i = splitIndex + 1; i < current->numOfSons; i++) {
			newNode->sons[j] = current->sons[i];
			if (current->sons[i] != nullptr) {
				current->sons[i]->parent = newNode;
			}
			j++;
			newNode->numOfSons++;
		}
		current->numOfSons = splitIndex + 1;
	}

	// If current is the root, create a new root
	if (current->parent == nullptr) {
		BNode* newRoot = new BNode(m);
		newRoot->records[0] = middleRecord;
		newRoot->numOfRecords = 1;
		newRoot->sons[0] = current;
		newRoot->sons[1] = newNode;
		newRoot->numOfSons = 2;
		current->parent = newRoot;
		newNode->parent = newRoot;
		root = newRoot;
	}
	else {
		// Insert middleRecord to parent
		BNode* parent = current->parent;
		parent->insert(middleRecord);

		// Find the position where the new node should be linked
		int pos;
		for (pos = 0; pos < parent->numOfSons; pos++) {
			if (parent->sons[pos] == current) {
				break;
			}
		}

		// Shift children of parent to make room for the new node
		for (int i = parent->numOfSons; i > pos + 1; i--) {
			parent->sons[i] = parent->sons[i - 1];
		}
		parent->sons[pos + 1] = newNode;
		parent->numOfSons++;

		// If parent is full, split it as well
		if (parent->numOfRecords == m) {
			split(parent);
		}
	}
}

template<class T>
T* BTree<T>::search(BNode* current, int key, int& counter)
{
	if (current == nullptr) return nullptr;

	counter++; // Count this node visit

	int i = 0;
	while (i < current->numOfRecords && key > current->records[i].getKey()) {
		i++;
	}

	if (i < current->numOfRecords && key == current->records[i].getKey()) {
		return &current->records[i]; // Found
	}

	if (current->isLeaf()) {
		return nullptr; // Not found
	}

	// Search in the next level
	return search(current->sons[i], key, counter);
}

template<class T>
T* BTree<T>::search(int key) {
	int counter = 0;
	T* result = nullptr;
	if (root != nullptr) {
		result = search(root, key, counter);
	}
	cout << "The search involved scanning " << counter << " nodes" << endl;
	return result;
}