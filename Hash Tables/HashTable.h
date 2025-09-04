//shira yaish, 327242939
//targil 2
#pragma once
#include <iostream>
#include "PrimeUtil.h"
using namespace std;

enum state { EMPTY, FULL, DELETED };

template<class K, class T>
class HashTable
{
protected:
    class Item
    {
    public:
        T data;         //The record information
        K key;          //The record key
        state flag;     //An indicator for the vacancy of the cell
        //Constructors
        Item() { flag = EMPTY; }
        Item(K k, T d) { data = d; key = k; flag = FULL; }
    };

    int size; // the table size (prime number)
    Item* table; // array of items (the hash table)

    int hash(K key, int i);
    virtual int h1(K key) = 0;
    virtual int h2(K key) = 0;

public:
    HashTable(int m = 10); //constructor
    ~HashTable();

    void insert(K key, T dat);  // 
    void remove(K key);
    int search(K key);
    void print();
    T& entryData(int i) //return value by index
    {
        return table[i].data;
    }
};

template<class K, class T >
HashTable<K, T>::HashTable(int m)
{
    if (m % 2 == 0)
        m++;
    while (!PrimeUtil::prime(m))
    {
        m = m + 2;
    }
    size = m;
    table = new Item[size]();
}

template<class K, class T>
HashTable<K, T>::~HashTable()
{
    delete[] table;
}

template <class K, class T>
int HashTable<K, T>::hash(K key, int i)
{
    return ((h1(key) + i * h2(key)) % size);
}

template <class K, class T>
int HashTable<K, T>::search(K key)
{
    for (int i = 0; i < size; i++)
    {
        int index = hash(key, i);

        if (table[index].flag == EMPTY) {
            return -1; // The key does not exist
        }

        if (table[index].flag == FULL && table[index].key == key) {
            return index; // The key is found
        }

        //If we got here, table[index].flag == DELETED or the key is different, continue searching
    }
    return -1; // The table is full and the key was not found
}

template <class K, class T>
void HashTable<K, T>::insert(K key, T dat)
{
    // First check if the key already exists
    if (search(key) != -1) {
        return; // The key already exists, do not enter it again
    }

    for (int i = 0; i < size; i++)
    {
        int index = hash(key, i);
        if (table[index].flag != FULL)
        {
            table[index].key = key;
            table[index].data = dat;
            table[index].flag = FULL;
            return;
        }
    }
    // If we got here, the table is full
}

template <class K, class T>
void HashTable<K, T>::remove(K key)
{
    int index = search(key);
    if (index != -1)
    {
        table[index].flag = DELETED;
    }
}

template<class K, class T>
void HashTable<K, T>::print()
{
    for (int i = 0; i < size; i++)
    {
        if (table[i].flag == FULL)
        {
            cout << i << ":\t" << table[i].key << '\n';
        }
    }
}