#include "LoanBookHeap.h"
#include <iostream>
#include <iomanip>
#include <sstream>


// Function to adjust the heap
void LoanBookHeap::heapifyUp(LoanBookHeapNode* pN) 
{
    
    while (pN != root && pN->getBookData()->getCode() < pN->getParent()->getBookData()->getCode()) {

        // Swap the book data
        LoanBookData* tempData = pN->getBookData();
        pN->setBookData(pN->getParent()->getBookData());
        pN->getParent()->setBookData(tempData);
        
        // Move to the parent node
        pN = pN->getParent();
    }
}

// adjust the heap downwards
void LoanBookHeap::heapifyDown(LoanBookHeapNode* pN) {

    // Continue adjusting down
    while (pN->getLeftChild() != nullptr) 
    {
        // Find the smaller child
        LoanBookHeapNode* smallerChild = pN->getLeftChild();
        if (pN->getRightChild() != nullptr && pN->getRightChild()->getBookData()->getCode() < smallerChild->getBookData()->getCode()) {
            smallerChild = pN->getRightChild();
        }

        if (pN->getBookData()->getCode() <= smallerChild->getBookData()->getCode()) {
            break;
        }

        // Swap the book data
        LoanBookData* tempData = pN->getBookData();
        pN->setBookData(smallerChild->getBookData());
        smallerChild->setBookData(tempData);

        // Move to the smaller child
        pN = smallerChild;
    }
}


// insert new data
bool LoanBookHeap::Insert(LoanBookData* data) {
    LoanBookHeapNode* newNode = new LoanBookHeapNode(data);

    if (root == nullptr) {
        root = newNode;
    }
    else {
        // Find the position
        LoanBookHeapNode* insertPosition = findInsertPosition(); 
        newNode->setParent(insertPosition);

        // Insert the new node
        if (insertPosition->getLeftChild() == nullptr) {
            insertPosition->setLeftChild(newNode);
        }
        else {
            insertPosition->setRightChild(newNode);
        }

        // Adjust the heap upwards
        heapifyUp(newNode);
    }

    return true;
}

// Function to find the next available position
LoanBookHeapNode* LoanBookHeap::findInsertPosition() {
    std::queue<LoanBookHeapNode*> nodeQueue;
    nodeQueue.push(root);

    // Level order traversal
    while (!nodeQueue.empty()) {
        LoanBookHeapNode* currentNode = nodeQueue.front();
        nodeQueue.pop();

        //less than two children is found
        if (!currentNode->getLeftChild() || !currentNode->getRightChild()) {
            return currentNode;
        }

        nodeQueue.push(currentNode->getLeftChild());
        nodeQueue.push(currentNode->getRightChild());
    }

    return nullptr;  
}


void LoanBookHeap::printHeap() 
{
    if (root == nullptr) 
    {  // If the heap is empty
        flog << "======== ERROR =========" << endl;
        flog << 500 << endl;  // Print the error code
        flog << "=======================" << endl << endl;
        return; 
    }

    std::queue<LoanBookHeapNode*> nodeQueue;
    nodeQueue.push(root);  // Start with the root

    flog << "========= PRINT_ST ==========" << endl;  

    while (!nodeQueue.empty()) {
        LoanBookHeapNode* currentNode = nodeQueue.front();  // Get the front node
        nodeQueue.pop();  // Remove the front node

        LoanBookData* bookData = currentNode->getBookData();
        if (bookData) {
            // Format the book code
            ostringstream formattedCode;
            formattedCode << setw(3) << setfill('0') << bookData->getCode();

            
            flog << bookData->getName() << "/"
                 << formattedCode.str() << "/"
                 << bookData->getAuthor() << "/"
                 << bookData->getYear() << "/"
                 << bookData->getLoanCount() << endl;
        }

        // Enqueue the left and right child
        if (currentNode->getLeftChild()) {
            nodeQueue.push(currentNode->getLeftChild());
        }
        if (currentNode->getRightChild()) {
            nodeQueue.push(currentNode->getRightChild());
        }
    }

    flog << "=============================" << endl;  
}
