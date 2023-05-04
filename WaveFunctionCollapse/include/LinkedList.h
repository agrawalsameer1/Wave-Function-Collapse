#ifndef LinkedList_h
#define LinkedList_h

#include <iostream>
#include <string>
#include "../include/WFC.h"
using namespace std;

struct Element
{
    WFC::Pattern pat;
    Element * next;
};

//*****************************************************************
// Linked lists store a variable number of items.
//*****************************************************************
class LinkedList
{
public:
    // Head is a reference to a list of data nodes.
    Element * head;
    
    // Length is the number of data nodes.
    int length;
    // Constructs the empty linked list object.
    // Creates the head node and sets length to zero.
    LinkedList();

    // Constructs linked list object with head node containing the WFC::Pattern
    LinkedList(WFC::Pattern pat);

    bool contains(WFC::Pattern pat);
    
    // Inserts an item at the end of the list.
    void insert( Element * newElement );
    
    // Removes an Element from the list by item key.
    // Returns true if the operation is successful.
    bool remove(WFC::Pattern Pat);
    
    // Searches for an item by its key.
    // Returns a reference to first match.
    // Returns a NULL pointer if no match is found.
    Element* get(WFC::Pattern Pat);
    
    // Returns the length of the list.
    int getLength();
    
    // De-allocates list memory when the program terminates.
    ~LinkedList();
};

#endif

//*****************************************************************
// End of File
//*****************************************************************