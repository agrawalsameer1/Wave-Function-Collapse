#pragma once

#ifndef LinkedList_h
#define LinkedList_h

#include <iostream>
#include <string>
#include "Structures.h"
using namespace std;

struct node
{
    Pattern pat;
    node * next;
};

//*****************************************************************
// Linked lists store a variable number of items.
//*****************************************************************
class LinkedList
{
public:
    // Head is a reference to a list of data nodes.
    node* head;
    
    // Length is the number of data nodes.
    int length;
    // Constructs the empty linked list object.
    // Creates the head node and sets length to zero.
    LinkedList();

    // Constructs linked list object with head node containing the WFC::Pattern
    LinkedList(Pattern* pat);

    LinkedList(node* head);

    void operator =(LinkedList link);

    bool contains(Pattern pat);
    
    // Inserts an item at the end of the list.
    void insert(node* newElement );
    
    // Removes an Element from the list by item key.
    // Returns true if the operation is successful.
    bool remove(Pattern Pat);
    
    // Searches for an item by its key.
    // Returns a reference to first match.
    // Returns a NULL pointer if no match is found.
    node* get(Pattern Pat);
    
    // Returns the length of the list.
    int getLength();
    
    // De-allocates list memory when the program terminates.
    ~LinkedList();
};

#endif

//*****************************************************************
// End of File
//*****************************************************************