#include "Book.h"
#include <algorithm>
#include <string>
#include <regex>
#include <list>
using namespace std;

Book::Book(const string& filepath) {
    // Open the file at the specified filepath
    ifstream file(filepath);
    // Check if the file is successfully opened
    if (file.is_open()) {
        // Read the entire content of the file into a stringstream
        stringstream buffer;
        buffer << file.rdbuf();
        content = buffer.str();
        file.close();
        // Transform the content to lowercase
        transform(content.begin(), content.end(), content.begin(), ::tolower);
        // Replace consecutive whitespaces with a single space using regular expressions
        regex pattern("\\s+"); // Matches one or more whitespace characters
        content = regex_replace(content, pattern, " ");
        // Insert content into the trie
        processContent();
    }
    else {
        // If the file fails to open, throw an exception
        throw invalid_argument("Unable to open file");
    }
}

void Book::processContent() {
    istringstream stream(content);
    string word1, word2, word3;
    vector<string> words;
    string word;

    // Read all words into vector
    while (stream >> word) {
        words.push_back(word);
    }

    // Create triplets with correct position calculation
    for (size_t i = 0; i <= words.size() - 3; i++) {
        string triplet = words[i] + " " + words[i + 1] + " " + words[i + 2];

        // Calculate the starting position of the first word in the original text
        size_t position = 0;
        size_t wordCount = 0;
        for (size_t j = 0; j < content.length() && wordCount <= i; j++) {
            if (!isWordBoundary(content[j])) {
                if (j == 0 || isWordBoundary(content[j - 1])) {
                    if (wordCount == i) {
                        position = j;
                        break;
                    }
                    wordCount++;
                }
            }
        }

        t.insert(triplet, position);
    }
}

void Book::searchAndPrint(const string& query) {
    list<int> locations = t.search(query);
    if (locations.empty()) {
        cout << "No results" << endl;
        return;
    }
    cout << "Sentences matching the prefix:" << endl;
    for (int location : locations) {
        string sentence = extractSentence(location);
        cout << sentence << endl;
    }
}

string Book::extractSentence(int location) {
    int startPos = location;
    int endPos = location;
    int beforeWordCount = 0;
    int totalWordCount = 0;
    bool hitPeriodBefore = false;
    bool hitPeriodAfter = false;

    // Search backwards - up to 5 words or a period
    while (startPos > 0 && beforeWordCount < 5 && !hitPeriodBefore) {
        startPos--;
        if (content[startPos] == '.') {
            startPos++; // repeat after the period
            hitPeriodBefore = true;
            break;
        }
        if (isWordBoundary(content[startPos]) && startPos + 1 < content.length() && !isWordBoundary(content[startPos + 1])) {
            beforeWordCount++;
        }
    }
    if (startPos == 0) hitPeriodBefore = true; //We have reached the beginning of the text

    // Count words from start to location
    for (int i = startPos; i < location; i++) {
        if (isWordBoundary(content[i]) && i + 1 < content.length() && !isWordBoundary(content[i + 1])) {
            totalWordCount++;
        }
    }

    // Search forward - until we reach 10 words in total or a period
    while (endPos < content.length() - 1 && totalWordCount < 10 && !hitPeriodAfter) {
        endPos++;
        if (content[endPos] == '.') {
            hitPeriodAfter = true;
            break;
        }
        if (isWordBoundary(content[endPos - 1]) && !isWordBoundary(content[endPos])) {
            totalWordCount++;
        }
    }
    if (endPos == content.length() - 1) hitPeriodAfter = true; // We have reached the end of the text

    // Sentence construction
    string before = content.substr(startPos, location - startPos);

    // Finding the end of a word/phrase that starts with location
    int queryEnd = location;
    while (queryEnd < content.length() && !isWordBoundary(content[queryEnd])) {
        queryEnd++;
    }
    // Continue reading two more words (if it's a threesome)
    int wordCount = 1;
    while (queryEnd < content.length() && wordCount < 3) {
        if (isWordBoundary(content[queryEnd])) {
            queryEnd++;
            if (queryEnd < content.length() && !isWordBoundary(content[queryEnd])) {
                wordCount++;
            }
        }
        else {
            queryEnd++;
        }
    }

    string after = content.substr(queryEnd, endPos - queryEnd + 1);

    // Add suspension points
    string beforeEllipsis = (!hitPeriodBefore && beforeWordCount >= 5) ? "..." : "";
    string afterEllipsis = (!hitPeriodAfter && totalWordCount >= 10) ? "..." : "";

    return beforeEllipsis + before + "*" + after + afterEllipsis;
}

void Book::censorQuery(const string& query) {
    t.remove(query);
}