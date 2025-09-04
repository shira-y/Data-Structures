#include "Book.h"

Book::Book(int catalog, int _shelf)
{
    catalogNumber = catalog;
    shelf = _shelf;
    available = true; 
}

bool Book::borrowBook()
{
    if (available == true)
    {
        available = false;
        cout << "Successfully found the book " << catalogNumber << " on shelf " << shelf << " and borrowed it" << endl;
        return true;
    }
    else
    {
        cout << "Error! The book " << catalogNumber << " is already borrowed!" << endl;
        return false;
    }
}

bool Book::returnBook()
{
    if (available == false)
    {
        available = true; 
        cout << "Successfully returned the book " << catalogNumber << " to shelf " << shelf << endl;
        return true;
    }
    else
    {
        cout << "Error! The book " << catalogNumber << " is not borrowed!" << endl;
        return false;
    }
}

ostream& operator<<(ostream& os, const Book& b) 
{
    os << "{" << b.catalogNumber << ", " << b.shelf << ", ";
    os << (b.available ? "available" : "borrowed") << "}";
    return os;
}

istream& operator>>(istream& is, Book& b)
{
    is >> b.catalogNumber >> b.shelf;
    b.available = true; 
    return is;
}