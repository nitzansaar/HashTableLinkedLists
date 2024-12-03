// Name: Nitzan Saar
// USC NetID: nsaar
// CSCI 455 PA5
// Fall 2024

#include <iostream>
#include <string>
#include <cassert>
using namespace std;

#include "listFuncs.h"
#include "Table.h"

// Function prototypes for our tests
void testListOperations();
void testTableBasics();
void testTableEdgeCases();
void testCollisions();
void testLargeDataset();

int main() {
    cout << "Running tests..." << endl;
    
    testListOperations();
    testTableBasics();
    testTableEdgeCases();
    testCollisions();
    testLargeDataset();
    
    cout << "All tests passed!" << endl;
    return 0;
}

// Test basic linked list operations
void testListOperations() {
    cout << "Testing list operations..." << endl;
    
    Node *head = NULL;
    
    // Test empty list
    assert(findNode(head, "any") == NULL);
    assert(!removeNode(head, "any"));
    assert(numNodes(head) == 0);
    
    // Test insertions
    assert(insertFront(head, "first", 1));
    assert(insertFront(head, "second", 2));
    assert(!insertFront(head, "first", 3));  // duplicate key
    assert(numNodes(head) == 2);
    
    // Test lookups
    assert(findNode(head, "first")->value == 1);
    assert(findNode(head, "second")->value == 2);
    assert(findNode(head, "third") == NULL);
    
    // Test removals
    assert(removeNode(head, "first"));
    assert(!removeNode(head, "first"));  // already removed
    assert(numNodes(head) == 1);
    
    // Clean up
    clearList(head);
    assert(head == NULL);
}

// Test basic Table operations
void testTableBasics() {
    cout << "Testing table basics..." << endl;
    
    // First set of tests with one table
    {
        Table t;
        
        // Test empty table
        assert(t.numEntries() == 0);
        assert(t.lookup("any") == NULL);
        assert(!t.remove("any"));
        
        // Test insertions
        assert(t.insert("apple", 1));
        assert(t.insert("banana", 2));
        assert(!t.insert("apple", 3));  // duplicate key
        assert(t.numEntries() == 2);
        
        // Test lookups
        assert(*t.lookup("apple") == 1);
        assert(*t.lookup("banana") == 2);
        assert(t.lookup("cherry") == NULL);
        
        // Test value updates
        int *val = t.lookup("apple");
        *val = 10;
        assert(*t.lookup("apple") == 10);
        
        // Test removals
        assert(t.remove("apple"));
        assert(!t.remove("apple"));  // already removed
        assert(t.numEntries() == 1);
    }
    
    // Second set of tests with a fresh table
    {
        Table t;
        
        // Test specific values and print them
        assert(t.insert("cat", 5));
        assert(t.insert("dog", 8));
        assert(t.insert("rat", 1));
        
        cout << "\nExpected output:" << endl;
        cout << "cat 5" << endl;
        cout << "dog 8" << endl;
        cout << "rat 1" << endl;
        
        cout << "\nActual output:" << endl;
        t.printAll();
        
        // Test hash stats
        cout << "\nHash stats for small example:" << endl;
        t.hashStats(cout);
    }
}

// Test edge cases
void testTableEdgeCases() {
    cout << "Testing edge cases..." << endl;
    
    // Test custom size constructor
    Table t(1);  // Very small table to force collisions
    
    // Test empty string key
    assert(t.insert("", 0));
    assert(*t.lookup("") == 0);
    assert(t.remove(""));
    
    // Test single character keys
    assert(t.insert("a", 1));
    assert(t.insert("b", 2));
    
    // Test long string keys
    string longKey(1000, 'x');  // 1000 'x' characters
    assert(t.insert(longKey, 100));
    assert(*t.lookup(longKey) == 100);
}

// Test collision handling
void testCollisions() {
    cout << "Testing collision handling..." << endl;
    
    // Create small table to force collisions
    Table t(5);
    
    // Insert several items (more than table size)
    for (int i = 0; i < 10; i++) {
        assert(t.insert("key" + to_string(i), i));
    }
    
    // Verify all items can be found
    for (int i = 0; i < 10; i++) {
        assert(*t.lookup("key" + to_string(i)) == i);
    }
    
    // Remove items in reverse order
    for (int i = 9; i >= 0; i--) {
        assert(t.remove("key" + to_string(i)));
    }
    
    assert(t.numEntries() == 0);
}

// Test with larger dataset
void testLargeDataset() {
    cout << "Testing large dataset..." << endl;
    
    Table t;
    const int NUM_ENTRIES = 1000;
    
    // Insert many items
    for (int i = 0; i < NUM_ENTRIES; i++) {
        string key = "key" + to_string(i);
        assert(t.insert(key, i));
    }
    
    assert(t.numEntries() == NUM_ENTRIES);
    
    // Verify all items
    for (int i = 0; i < NUM_ENTRIES; i++) {
        string key = "key" + to_string(i);
        assert(*t.lookup(key) == i);
    }
    
    // Test statistics
    cout << "\nHash table statistics for large dataset:" << endl;
    t.hashStats(cout);
}
