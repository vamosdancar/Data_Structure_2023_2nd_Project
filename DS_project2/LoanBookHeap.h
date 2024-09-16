#pragma once
#include "LoanBookData.h"
#include "LoanBookHeapNode.h"
#include <queue>
#include <fstream>

class LoanBookHeap
{
private:
    LoanBookHeapNode* root; // Root of the loan book heap
    std::ofstream flog;  // file stream variable

public:
    // Constructor
    LoanBookHeap(const std::string& logFilePath) {
        root = nullptr;
        flog.open(logFilePath, std::ios::app);  

    };
    
    // Destructor
    ~LoanBookHeap() {
            if (flog.is_open()) {
            flog.close();  
        }
    }

    // Setter and getter
    void setRoot(LoanBookHeapNode* pN) { this->root = pN; }
    LoanBookHeapNode* getRoot() { return root; }

    // Method declarations
    void heapifyUp(LoanBookHeapNode* pN);    // Adjusts the heap upwards
    void heapifyDown(LoanBookHeapNode* pN);  // Adjusts the heap downwards

    bool Insert(LoanBookData* data);         // Inserts new data
    LoanBookHeapNode* findInsertPosition();  // Finds the position

    // print the heap contents
    void printHeap();
};
