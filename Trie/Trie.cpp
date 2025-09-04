#include "Trie.h"
#include <iostream>

void Trie::insert(const std::string& word, int pos) {
    TrieNode* current = root;
    for (char ch : word) {
        if (current->children.find(ch) == current->children.end()) {
            current->children[ch] = new TrieNode(current);
        }
        current = current->children[ch];
    }
    current->isWordEnd = true;
    current->positions.push_back(pos);
}

std::list<int> Trie::search(const std::string& word) {
    std::list<int> results;
    int visitedNodes = 0;
    TrieNode* node = findNode(word, visitedNodes);
    if (node != nullptr) {
        collectResults(node, results, visitedNodes);
    }
    std::cout << "The search required visiting " << visitedNodes << " nodes." << std::endl;
    return results;
}

void Trie::remove(const std::string& word) {
    int visitedNodes = 0;
    TrieNode* node = findNode(word, visitedNodes);
    if (node != nullptr && node->isWordEnd) {
        node->isWordEnd = false;
        node->positions.clear();
    }
}

Trie::TrieNode* Trie::findNode(const std::string& str, int& visitedNodes) {
    TrieNode* current = root;
    visitedNodes = 1;  // Start from 1 to count the root node
    for (char ch : str) {
        if (current->children.find(ch) == current->children.end()) {
            return nullptr;
        }
        current = current->children[ch];
        visitedNodes++;
    }
    return current;
}

void Trie::collectResults(TrieNode* node, std::list<int>& results, int& visitedNodes) {
    if (results.size() >= 3) return;

    // If the current vertex represents the end of a string, add the positions
    if (node->isWordEnd) {
        for (int pos : node->positions) {
            if (results.size() < 3) {
                results.push_back(pos);
            }
            else {
                return;
            }
        }
    }

    // Continue scanning pre-order on children
    for (auto& child : node->children) {
        if (results.size() >= 3) break;
        visitedNodes++;
        collectResults(child.second, results, visitedNodes);
    }
}