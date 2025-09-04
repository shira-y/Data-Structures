#pragma once
#include<iostream>
using namespace std;

class Book
{
private:
    int catalogNumber;
    int shelf;
    bool available;
public:
    int getKey() const { return catalogNumber; }
    Book(int catalog = 0, int _shelf = 0);
    bool borrowBook();
    bool returnBook();

    bool operator<(const Book& b) const { return catalogNumber < b.catalogNumber; }
    bool operator>(const Book& b) const { return catalogNumber > b.catalogNumber; }
    bool operator<=(const Book& b) const { return catalogNumber <= b.catalogNumber; }
    bool operator>=(const Book& b) const { return catalogNumber >= b.catalogNumber; }
    bool operator==(const Book& b) const { return catalogNumber == b.catalogNumber; }
    bool operator!=(const Book& b) const { return catalogNumber != b.catalogNumber; }

    friend ostream& operator<<(ostream& os, const Book& b);
    friend istream& operator>>(istream& is, Book& b);
};