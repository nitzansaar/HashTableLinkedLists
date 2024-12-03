// Name: Nitzan Saar
// USC NetID: nsaar
// CSCI 455 PA5
// Fall 2024

#include "Table.h"
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

void printCommandSummary() {
    cout << "insert name score    Insert this name and score in the grade table" << endl;
    cout << "change name newscore Change the score for name" << endl;
    cout << "lookup name          Lookup the name, and print out his or her score" << endl;
    cout << "remove name          Remove this student" << endl;
    cout << "print                Prints out all names and scores in the table" << endl;
    cout << "size                 Prints out the number of entries in the table" << endl;
    cout << "stats                Prints out statistics about the hash table" << endl;
    cout << "help                 Prints out a brief command summary" << endl;
    cout << "quit                 Exits the program" << endl;
}

int main(int argc, char * argv[]) {
    Table *grades;  

    // Handle command line argument for hash table size
    if (argc > 1) {
        int hashSize = atoi(argv[1]);  
        grades = new Table(hashSize);
    }
    else {   
        grades = new Table();
    }

    // Print initial stats
    grades->hashStats(cout);

    string command;
    
    cout << "cmd> ";  // Initial prompt
    while (cin >> command) {
        if (command == "insert") {
            string name;
            int score;
            cin >> name >> score;
            if (!grades->insert(name, score)) {
                cout << "name already present" << endl;
            }
        }
        else if (command == "change") {
            string name;
            int score;
            cin >> name >> score;
            int *oldScore = grades->lookup(name);
            if (oldScore == NULL) {
                cout << "name not present" << endl;
            }
            else {
                *oldScore = score;
            }
        }
        else if (command == "lookup") {
            string name;
            cin >> name;
            int *score = grades->lookup(name);
            if (score == NULL) {
                cout << "name not present" << endl;
            }
            else {
                cout << *score << endl;
            }
        }
        else if (command == "remove") {
            string name;
            cin >> name;
            if (!grades->remove(name)) {
                cout << "name not present" << endl;
            }
        }
        else if (command == "print") {
            grades->printAll();
        }
        else if (command == "size") {
            cout << grades->numEntries() << endl;
        }
        else if (command == "stats") {
            grades->hashStats(cout);
        }
        else if (command == "help") {
            printCommandSummary();
        }
        else if (command == "quit") {
            break;
        }
        else {
            cout << "ERROR: invalid command" << endl;
            printCommandSummary();
        }
        
        cout << "cmd> ";  // Prompt for next command
    }

    delete grades;
    return 0;
}
