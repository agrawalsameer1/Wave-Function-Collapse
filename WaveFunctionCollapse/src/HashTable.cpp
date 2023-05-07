//*****************************************************************
//  HashTable.cpp
//  HashTable
//
//  This header file contains the Hash Table class definition.
//  Hash Table array elements consist of Linked List objects.
//*****************************************************************

#include "../include/HashTable.h"

// Constructs the empty Hash Table object.
// Array length is set to 13 by default.
HashTable::HashTable(int tableLength)
{
    if (tableLength <= 0) {
        tableLength = 16;
    }
    array = new LinkedList[tableLength];
    length = tableLength;
    filled = 0;
}

bool HashTable::contains(Pattern pat) {
    for (int i = 0; i < filled; i++) {
        if (array[i].head->pat.pixels == pat.pixels) {
            return true;
        }
    }
    return false;
}

bool HashTable::contains(Pattern pat, int length) {
    int max = length < filled ? length:filled;
    for (int i = 0; i < max; i++) {
        if (array[i].head->pat.pixels == pat.pixels) {
            return true;
        }
    }
    return false;
}

// Adds an item to the Hash Table.
void HashTable::insert(Pattern pat)
{
    bool inTable = false;
    node* element = (node*)(malloc(sizeof(node)));
    element->pat = pat;
    for (int i = 0; i < filled; i++) {
        if (array[i].head->pat.pixels == pat.pixels) {
            array[i].insert(element);
            inTable = true;
        }
    }

    if (!(inTable)) {
        array[filled] = *(new LinkedList(pat));
        filled++;
    }
}

LinkedList HashTable::get(int index) {
    return array[index];
}

// Returns an Element from the Hash Table by key.
// If the Element isn't found, a null pointer is returned.
LinkedList HashTable::get(Pattern pat)
{
    for (int i = 0; i < filled; i++) {
        if (array[i].head->pat.pixels == pat.pixels) {
            return array[i];
        }
    }
}

// Returns the number of locations in the Hash Table.
int HashTable::getLength()
{
    return length;
}

// Returns the number of Items in the Hash Table.
int HashTable::getNumberOfElements()
{
    return filled;
}