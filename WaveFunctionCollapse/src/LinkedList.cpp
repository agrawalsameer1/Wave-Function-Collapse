//*****************************************************************
//  LinkedList.cpp
//  HashTable

//
//  This header file contains the Linked List class declaration.
//  Hash Table array elements consist of Linked List objects.
//*****************************************************************

#include "../include/LinkedList.h"

// Constructs the empty linked list object.
// Creates the head node and sets length to zero.
LinkedList::LinkedList()
{
    head = (node*)(malloc(sizeof(node)));
    length = 0;
}

LinkedList::LinkedList(WFC::Pattern pat) {
    head = (node*)(malloc(sizeof(node)));;
    head->pat = pat;
    length = 0;
}

// Inserts an item at the end of the list.
void LinkedList::insert(node * newElement )
{
    node* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    current->next = newElement;
    length++;
  // * * * * * * * * * * *
  // Your code goes here
  // * * * * * * * * * * *
}

// Removes an item from the list by item key.
// Returns true if the operation is successful.
bool LinkedList::remove(WFC::Pattern pat)
{
    node* traverser = head;

    while ((!(traverser->next->pat.pixels == pat.pixels)) && (traverser->next->next)) {
        traverser = traverser->next;
    }
    if (traverser->next->pat.pixels == pat.pixels) {
        node* tmp = traverser->next;
        traverser->next = traverser->next->next;
        delete tmp;
        length--;
        return true;
    }
    else {
        return false;
    }
}

bool LinkedList::contains(WFC::Pattern pat) {
    node* getter = get(pat);
    if (getter == nullptr) {
        return false;
    }
    else {
        return true;
    }
}
  // * * * * * * * * * * *
  // Your code goes here
  // * * * * * * * * * * *

// Searches for an item by its key.
// Returns a reference to first match.
// Returns a NULL pointer if no match is found.
node* LinkedList::get(WFC::Pattern pat)
{
    node* traverser = head;
    while ((!(traverser->pat.pixels == pat.pixels)) && (traverser->next)) {
        traverser = traverser->next;
    } 
    if (traverser->pat.pixels == pat.pixels) {
        return traverser;
    }
    else {
        return nullptr;
    }
  // * * * * * * * * * * *
  // Your code goes here
  // * * * * * * * * * * *
}

// Returns the length of the list.
int LinkedList::getLength()
{
    return length;
}

// De-allocates list memory when the program terminates.
LinkedList::~LinkedList()
{
    node* traverser = head;
    node* traverser2 = traverser;
    while (traverser2->next) {
        node* traverser = traverser2;
        traverser2 = traverser->next;
        delete traverser;
    }
  // * * * * * * * * * * *
  // Your code goes here
  // * * * * * * * * * * *
}

//*****************************************************************
// End of File
//*****************************************************************