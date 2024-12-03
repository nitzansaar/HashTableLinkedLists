// Name: Nitzan Saar
// USC NetID: nsaar
// CSCI 455 PA5
// Fall 2024

#include <iostream>
#include <string>
#include <cctype>
using namespace std;

#include "Table.h"

// Function prototypes
string cleanWord(const string &word);
bool isWord(const string &word);

int main() {
    Table wordTable;
    string word;
    
    // Read words from input
    while (cin >> word) {
        word = cleanWord(word);
        if (isWord(word)) {
            int *count = wordTable.lookup(word);
            if (count == NULL) {
                wordTable.insert(word, 1);
            } else {
                (*count)++;
            }
        }
    }
    
    // Print results
    wordTable.printAll();
    
    return 0;
}

// Remove punctuation and convert to lowercase
// Returns empty string if the word contains no letters
string cleanWord(const string &word) {
    string result;
    bool lastWasLetter = false;
    
    for (char c : word) {
        if (isalpha(c)) {
            result += tolower(c);
            lastWasLetter = true;
        } else {
            // If we hit a non-letter, break the word
            if (lastWasLetter) break;
        }
    }
    
    return result;
}

// Returns true if the string contains at least one letter
bool isWord(const string &word) {
    return word.length() > 0;
}

