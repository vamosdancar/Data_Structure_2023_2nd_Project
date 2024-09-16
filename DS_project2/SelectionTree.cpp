#include "SelectionTree.h"

// Function to insert new data 
bool SelectionTree::Insert(LoanBookData* newData) {
    SelectionTreeNode* newNode = new SelectionTreeNode();  
    // new SelectionTreeNode

newNode->setBookData(newData);  // Set the book data

if (root == nullptr) {  // make the new node the root.
    root = newNode;
    return true;
}

SelectionTreeNode* current = root;  // Initialize a pointer 
SelectionTreeNode* parent = nullptr;  // Initialize a pointer 

// Traverse the tree to
while (current != nullptr) {
    parent = current;  // Update parent
    
    // Compare the code of the new data
    if (newData->getCode() < current->getBookData()->getCode()) {
        current = current->getLeftChild();  // Move to the left child
    } else {
        current = current->getRightChild();  // Move to the right child
    }
}

newNode->setParent(parent);  // Set the parent of the new node

if (newData->getCode() < parent->getBookData()->getCode()) {
    parent->setLeftChild(newNode);  // Set the new node
} else {
    parent->setRightChild(newNode);  // Set the new node
}

return true;
}



// Function to delete a node
bool SelectionTree::Delete() 
{
      if (root == nullptr) {
        *fout << "Error Code: Tree is empty" << std::endl;  // Adjust the error message as needed
        return false;
    }
}

// Function to print book data
bool SelectionTree::printBookData(int bookCode) 
{
    SelectionTreeNode* current = root;
    while (current != nullptr) {
        // print the book data
        if (bookCode == current->getBookData()->getCode()) {
            LoanBookData* bookData = current->getBookData();
            cout << bookData->getName() << "/" << bookData->getAuthor() << "/ " << bookData->getYear() << endl;
            return true;
        }
        // Move to the left or right child
        current = (bookCode < current->getBookData()->getCode()) ? current->getLeftChild() : current->getRightChild();
    }
    // Return false 
    return false;
}
