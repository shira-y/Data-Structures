//shira yaish, 327242939
//targil 2
#pragma once
#include <iostream>
#include "HashTable.h"
using namespace std;

template <class T>
class StringHash :public HashTable <string, T>
{
private:
    int h1(string s)
    {
        unsigned long long sum = 0;
        unsigned long long base = 1;

        for (int i = 0; i < s.length() && i < 8; i++) // Limit to 8 characters
        {
            sum = (sum + (unsigned char)s[i] * base) % this->size;
            base = (base * 256) % this->size;
        }
        return sum;
    }

    int h2(string s) {
        return 1; // linear scan
    }

public:
    StringHash(int m = 10) :HashTable<string, T>(m) {}
};