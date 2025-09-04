#pragma once
#include <string>
#include <map>
#include <list>

class Trie {
private:
    class TrieNode {
    public:
        TrieNode* parent;
        std::map<char, TrieNode*> children;
        bool isWordEnd;
        std::list<int> positions;

        TrieNode(TrieNode* parent = nullptr) : parent(parent), isWordEnd(false) {}
        ~TrieNode() {
            for (auto& pair : children) {
                delete pair.second;
            }
        }
    };

    TrieNode* root;

    TrieNode* findNode(const std::string& str, int& visitedNodes);
    void collectResults(TrieNode* node, std::list<int>& results, int& visitedNodes);

public:
    Trie() : root(new TrieNode()) {}
    ~Trie() { delete root; }

    void insert(const std::string& word, int pos);
    std::list<int> search(const std::string& word);
    void remove(const std::string& word);
};