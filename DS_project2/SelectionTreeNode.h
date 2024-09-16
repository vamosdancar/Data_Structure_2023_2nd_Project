#pragma once
#include "LoanBookData.h"
#include "LoanBookHeap.h"

class SelectionTreeNode
{
private:
    LoanBookData* pData;            // loan book data
    SelectionTreeNode* pLeft;       // left child node
    SelectionTreeNode* pRight;      // right child node
    SelectionTreeNode* pParent;     // parent node
    LoanBookHeap* hRoot;            // loan book heap
     LoanBookHeap* heap;

public:
    // Constructor
    SelectionTreeNode() {
        this->pData = NULL;
        this->pLeft = NULL;
        this->pRight = NULL;
        this->pParent = NULL;
        this->hRoot = NULL;
        heap = new LoanBookHeap("log.txt"); 
    }

    // Destructor
    ~SelectionTreeNode() {
        delete heap;    
    }

    // Setters for the node attributes
    void setBookData(LoanBookData* data) { this->pData = data; }
    void setLeftChild(SelectionTreeNode* pL) { this->pLeft = pL; }
    void setRightChild(SelectionTreeNode* pR) { this->pRight = pR; }
    void setParent(SelectionTreeNode* pP) { this->pParent = pP; }
    void setHeap(LoanBookHeap* pHR) { this->hRoot = pHR; }

    // deep copy of the loan book heap
    LoanBookHeapNode* deepCopy(LoanBookHeapNode* root) 
    {
        if (root == NULL) return nullptr;

        LoanBookHeapNode* copy = new LoanBookHeapNode();
        copy->setBookData(root->getBookData()); // Copy the data
        copy->setLeftChild(deepCopy(root->getLeftChild())); // Recursively copy 
        copy->setRightChild(deepCopy(root->getRightChild())); // Recursively copy

        return copy;
    }

    //node attributes
    LoanBookData* getBookData() { return pData; }
    SelectionTreeNode* getLeftChild() { return pLeft; }
    SelectionTreeNode* getRightChild() { return pRight; }
    SelectionTreeNode* getParent() { return pParent; }
    LoanBookHeap* getHeap() { return hRoot; }
    LoanBookHeap* heaps() { return heap; }
    void setheaps(LoanBookHeap* aa) { heap = aa; }
};
