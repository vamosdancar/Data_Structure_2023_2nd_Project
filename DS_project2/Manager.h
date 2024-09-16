#pragma once
#include "SelectionTree.h"
#include "BpTree.h"
#include <map>
#include <string>
#include <fstream>

class Manager
{
private:
    char* cmd;                          
    BpTree* bptree;                     // Pointer B+ tree
    SelectionTree* stree;               // Pointer selection tree

public:
    ifstream fin;                       
    ofstream flog;                      

    // Constructor
    Manager(int bpOrder) : flog() {
        bptree = new BpTree(&flog, bpOrder);
        stree = new SelectionTree(&flog);
    }

    // Destructor
    ~Manager() {
        delete bptree;
        delete stree;
    }

    // Method prototypes
    void run(const char* command);       // Runs the given command
    bool LOAD();                         // Loads data 
    bool ADD();                          // Adds data

    bool SEARCH_BP_BOOK(string name);    // Searches for a book
    bool SEARCH_BP_RANGE(string start, string end); // Searches for books

    bool PRINT_BP();                     // Prints the B+ tree
    bool PRINT_ST(int categoryCode);                     // Prints the selection tree

    bool DELETE();                       // Deletes data 

    void printErrorCode(int n);          // Prints an error code
    void printSuccessCode(const string& name); // Prints a success code
    void SuccessADD(const string& action, string& name, int code_str, string& author, int year_str); // Prints success message
    void SuccessSearch(const string& action, const string& name, int code_str, const string& author, int year_str, int loan); // Prints success message
};
