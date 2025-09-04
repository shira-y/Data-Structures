#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Trie.h"

using namespace std;

class Book {
private:
    string content;
    Trie t;
    void processContent();
    bool isWordBoundary(char c) {
        return c == ' ' || c == '.' || c == ',' || c == '\n' || c == '\t';
    }

public:
    Book(const string& filepath);
    string extractSentence(int location);
    void searchAndPrint(const string& query);
    void censorQuery(const string& query);
};