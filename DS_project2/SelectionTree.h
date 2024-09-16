#pragma once
#include "SelectionTreeNode.h"

#include <fstream>
#include <iostream>

class SelectionTree
{
private:
    SelectionTreeNode* root;        // Root
    ofstream* fout;                 // Output file stream

public:
    // Constructor
    SelectionTree(ofstream* fout) {
        this->root = NULL;
        this->fout = fout;
    }
    // Destructor
    ~SelectionTree() {

    }

    // Setter and getter 
    void setRoot(SelectionTreeNode* pN) { this->root = pN; }
    SelectionTreeNode* getRoot() { return root; }

    // Function prototypes 
    bool Insert(LoanBookData* newData); // insert a new node
    bool Delete();                      // delete a node
    bool printBookData(int bookCode);   // print book data based on a book code

    // Method to find a node
    SelectionTreeNode* findNode(int bookCode) {
    SelectionTreeNode* current = root;
    while (current != nullptr) {
        if (current->getBookData() && current->getBookData()->getCode() == bookCode) {
            return current; // if got a fing
        } else if (bookCode < current->getBookData()->getCode()) {
            current = current->getLeftChild(); // go to the left child
        } else {
            current = current->getRightChild(); // go to the right child
        }
    }
    return nullptr; // if got a fail
}

};
