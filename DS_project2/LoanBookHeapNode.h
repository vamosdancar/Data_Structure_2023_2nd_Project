#pragma once
#include "LoanBookData.h"

class LoanBookHeapNode
{
private:
    LoanBookData* pData;                // loan book data
    LoanBookHeapNode* pLeft;            // left child node
    LoanBookHeapNode* pRight;           // right child node
    LoanBookHeapNode* pParent;          // parent node

public:
    // Default constructor
    LoanBookHeapNode() {
        this->pData = NULL;
        this->pLeft = NULL;
        this->pRight = NULL;
        this->pParent = NULL;
    }

    // Constructor with LoanBookData argument
    LoanBookHeapNode(LoanBookData* data) {
        this->pData = data;
        this->pLeft = NULL;
        this->pRight = NULL;
        this->pParent = NULL;
    }
    
    // Destructor
    ~LoanBookHeapNode() {

    }

    // Setter methods
    void setBookData(LoanBookData* data) { this->pData = data; }
    void setLeftChild(LoanBookHeapNode* pL) { this->pLeft = pL; }
    void setRightChild(LoanBookHeapNode* pR) { this->pRight = pR; }
    void setParent(LoanBookHeapNode* pP) { this->pParent = pP; }

    // Getter methods
    LoanBookData* getBookData() { return pData; }
    LoanBookHeapNode* getLeftChild() { return pLeft; }
    LoanBookHeapNode* getRightChild() { return pRight; }
    LoanBookHeapNode* getParent() { return pParent; }
};
