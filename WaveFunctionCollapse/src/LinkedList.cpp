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
    head->next = nullptr;
    length = 0;
}

LinkedList::LinkedList(Pattern* pat) {
    head = (node*)(malloc(sizeof(node)));
    head->pat = *pat;
    head->next = nullptr;
    length = 1;
}

LinkedList::LinkedList(node* inHead) {
    node* traverser = inHead;
    length = 0;
    while (traverser != nullptr) {
        length++;
        traverser = traverser->next;
    }
}

void LinkedList::operator=(LinkedList l) {
    node* traverser = l.head;
    node* traverser2 = head;

    while (traverser != nullptr) {
        traverser2->pat = traverser->pat;
        traverser2->next = traverser->next;
        traverser2 = traverser2->next;
        traverser = traverser->next;
    }
}

// Inserts an item at the end of the list.
void LinkedList::insert(node* newElement )
{
    //std::cout << "\nin insert\n";

    if (length == 0) {
        head->pat = newElement->pat;
        head->next = nullptr;
        //std::cout << "no head\n";
    }
    else if (length == 1) {
        head->next = newElement;
        //std::cout << "no head next\n";
        //std::cout << head->pat.N << "\n";
    }
    else {
        //std::cout << "head N:" << head->pat.N << "\n";
        node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        //std::cout << "insert called\n";
        current->next = newElement;
        //std::cout << "head N:" << head->pat.N << "\n";
        //std::cout << current->next << "\n";
    }
    length++;
}

// Removes an item from the list by item key.
// Returns true if the operation is successful.
bool LinkedList::remove(Pattern pat)
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

bool LinkedList::contains(Pattern pat) {
    node* getter = get(pat);
    if (getter == nullptr) {
        return false;
    }
    else {
        return true;
    }

}

// Searches for an item by its key.
// Returns a reference to first match.
// Returns a NULL pointer if no match is found.
node* LinkedList::get(Pattern pat)
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

}
