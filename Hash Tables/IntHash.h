
//shira yaish, 327242939
//targil 2

#pragma once
#include"HashTable.h"
#include<string>
using namespace std;
template <class T>
class IntHash :public HashTable<int, T>
{
private:
	
	//TODO: implement h1 and h2
	int h1(int k) { return k % this->size; }
	int h2(int k) { return ((k % (this->size - 1)) + 1) ; }
public:
	IntHash(int m = 10) :HashTable<int, T>(m) {}
};
