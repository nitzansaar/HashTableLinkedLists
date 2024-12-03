// Name: Nitzan Saar
// USC NetID: nsaar 
// CSCI 455 PA5
// Fall 2024


#include <iostream>

#include <cassert>

#include "listFuncs.h"

using namespace std;

Node::Node(const string &theKey, int theValue) {
   key = theKey;
   value = theValue;
   next = NULL;
}

Node::Node(const string &theKey, int theValue, Node *n) {
   key = theKey;
   value = theValue;
   next = n;
}




//*************************************************************************
// put the function definitions for your list functions below

// Returns pointer to the node containing the given key, or NULL if key not found
Node * findNode(Node *head, const string &key) {
    Node *curr = head;
    while (curr != NULL) {
        if (curr->key == key) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

// Inserts a new node at the front of the list
// Returns true if inserted, false if key already exists
bool insertFront(Node * &head, const string &key, int value) {
    if (findNode(head, key) != NULL) {
        return false;  // key already exists
    }
    head = new Node(key, value, head);
    return true;
}

// Removes node with given key
// Returns true if removed, false if key not found
bool removeNode(Node * &head, const string &key) {
    if (head == NULL) return false;
    
    if (head->key == key) {
        Node *temp = head;
        head = head->next;
        delete temp;
        return true;
    }
    
    Node *curr = head;
    while (curr->next != NULL) {
        if (curr->next->key == key) {
            Node *temp = curr->next;
            curr->next = temp->next;
            delete temp;
            return true;
        }
        curr = curr->next;
    }
    return false;
}

// Returns number of nodes in the list
int numNodes(Node *head) {
    int count = 0;
    Node *curr = head;
    while (curr != NULL) {
        count++;
        curr = curr->next;
    }
    return count;
}

// Prints all nodes in the list in format: key value
void printList(Node *head) {
    Node *curr = head;
    while (curr != NULL) {
        cout << curr->key << " " << curr->value << endl;
        curr = curr->next;
    }
}

// Deallocates all nodes in the list
void clearList(Node * &head) {
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
}
