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
HashTable::HashTable(int tableLength) {
    if (tableLength <= 0) {
        tableLength = 16;
    }
    length = tableLength;
    array = new LinkedList*[ tableLength ];
    filled = 0;
}

void HashTable::operator=(HashTable h) {
    for (int i = 0; i < h.getNumberOfElements(); i++) {
        LinkedList* l = h.array[i];
        array[i] = l;
    }
}

bool HashTable::contains(Pattern* patt) {
    for (int i = 0; i < filled; i++) {
        if (array[i]->head->pat.pixels == patt->pixels) {
            return true;
        }
    }
    return false;
}

bool HashTable::contains(Pattern* patt, int len) {
    int max = len < filled ? len:filled;
    for (int i = 0; i < max; i++) {
        if (array[i]->head->pat.pixels == patt->pixels) {
            return true;
        }
    }
    return false;
}

// Adds an item to the Hash Table.
void HashTable::insert(Pattern* key, Pattern* Pat)
{
    bool inTable = false;
    node* element = (node*)(malloc(sizeof(node)));
    element->pat = *Pat;

    if (contains(key)) {
        std::cout << "else this\n";
        get(key)->insert(element);
        
    }
    else {
        LinkedList* link = new LinkedList(Pat);
        array[filled] = link;
        filled++;
    }
}

void HashTable::insert(int key, Pattern* Pat)
{
    //std::cout << "in hash table insert\n";
    if (key >= filled) {
        LinkedList* link = new LinkedList(Pat);
        array[filled] = link;
        filled++;
    }
    else {
        node* element = (node*)(malloc(sizeof(node)));
        element->pat = *Pat;
        array[key]->insert(element);
        //std::cout << "\n\ninserting pixels:\n" << element->pat.pixels;
       // LinkedList* linky = new LinkedList(head);
        //array[key] = *linky;
        
        //std::cout << "did we make it\n";
        //std::cout << "N IN HASH:\n" << array[key].head->pat.pixels << "\n";
    }
}

LinkedList* HashTable::get(int index) {
    return array[index];
}

// Returns an Element from the Hash Table by key.
// If the Element isn't found, a null pointer is returned.
LinkedList* HashTable::get(Pattern* patt)
{
    for (int i = 0; i < filled; i++) {
        if (array[i]->head->pat.pixels == patt->pixels) {
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