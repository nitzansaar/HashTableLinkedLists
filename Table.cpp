// Name: Nitzan Saar
// USC NetID: nsaar
// CSCI 455 PA5
// Fall 2024

// Table.cpp  Table class implementation

#include "Table.h"
#include <iostream>
#include <string>
#include <cassert>
#include "listFuncs.h"

using namespace std;

// create an empty table, i.e., one where numEntries() is 0
// (Underlying hash table is HASH_SIZE.)
Table::Table() : hashSize(HASH_SIZE) {
    hashTable = new ListType[hashSize]();  // Initialize all entries to NULL
}

// create an empty table, i.e., one where numEntries() is 0
// such that the underlying hash table is hSize
Table::Table(unsigned int hSize) : hashSize(hSize) {
    hashTable = new ListType[hashSize]();  // Initialize all entries to NULL
}

// returns the pointer to the value that goes with this key
// or NULL if key is not present.
int* Table::lookup(const string &key) {
    unsigned int hashVal = hashCode(key);
    Node* found = findNode(hashTable[hashVal], key);
    return found ? &(found->value) : NULL;
}

// remove a pair given its key
// returns true iff found and removed
bool Table::remove(const string &key) {
    unsigned int hashVal = hashCode(key);
    return removeNode(hashTable[hashVal], key);
}

// insert a new pair into the table
// returns true iff new entry inserted successfully
bool Table::insert(const string &key, int value) {
    unsigned int hashVal = hashCode(key);
    
    // Check if key already exists
    if (lookup(key) != NULL) {
        return false;
    }
    
    // Insert at front of list for this hash value
    return insertFront(hashTable[hashVal], key, value);
}

// number of entries in the table
int Table::numEntries() const {
    int total = 0;
    for (unsigned int i = 0; i < hashSize; i++) {
        total += numNodes(hashTable[i]);
    }
    return total;
}

// print out all the entries in the table, one per line
void Table::printAll() const {
    for (unsigned int i = 0; i < hashSize; i++) {
        if (hashTable[i] != NULL) {  // Only print non-empty buckets
            printList(hashTable[i]);
        }
    }
}

// hashStats: print out info to let us know if we're getting a good distribution
void Table::hashStats(ostream &out) const {
    int numBuckets = hashSize;
    int numEmpty = 0;
    int maxLen = 0;
    
    // Count empty buckets and find longest chain
    for (unsigned int i = 0; i < hashSize; i++) {
        int chainLen = numNodes(hashTable[i]);
        if (chainLen == 0) {
            numEmpty++;
        }
        if (chainLen > maxLen) {
            maxLen = chainLen;
        }
    }
    
    // Calculate average chain length for non-empty buckets
    double avgLen = 0.0;
    if (numBuckets - numEmpty > 0) {
        avgLen = static_cast<double>(numEntries()) / (numBuckets - numEmpty);
    }
    
    out << "number of buckets: " << numBuckets << endl;
    out << "number of entries: " << numEntries() << endl;
    out << "number of empty buckets: " << numEmpty << endl;
    out << "longest chain: " << maxLen << endl;
    out << "average chain length for non-empty buckets: " << avgLen << endl;
}

// hash function for a string
// (we defined it for you)
unsigned int Table::hashCode(const string &word) const {
   return hash<string>()(word) % hashSize;
}

// destructor
Table::~Table() {
    for (unsigned int i = 0; i < hashSize; i++) {
        clearList(hashTable[i]);
    }
    delete [] hashTable;
}

