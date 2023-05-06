#include "LinkedList.h"

class HashTable
{
private:
    // Length is the size of the Hash Table array.
    int length;
    int filled;
    
public:
    LinkedList* array;
    
    // Constructs the empty Hash Table object.
    // Array length is set to 13 by default.
    HashTable( int tableLength = 13 );

    bool contains(WFC::Pattern pat);

    bool contains(WFC::Pattern pat, int length);
    
    // Adds an item to the Hash Table.
    void insert(WFC::Pattern pat);
    
    // Deletes an Item by key from the Hash Table.
    // Returns true if the operation is successful.
    bool erase( string Key );
    
    // Returns an item from the Hash Table by key.
    // If the item isn't found, a null pointer is returned.
    LinkedList get(WFC::Pattern pat);


    LinkedList get(int index);
    
    // Display the contents of the Hash Table to console window.
    void printTable();
    
    // Prints a histogram illustrating the Item distribution.
    void printHistogram();
    
    // Returns the number of locations in the Hash Table.
    int getLength();
    
    // Returns the number of Items in the Hash Table.
    int getNumberOfElements();
    
    // De-allocates all memory used for the Hash Table.
    ~HashTable();
};