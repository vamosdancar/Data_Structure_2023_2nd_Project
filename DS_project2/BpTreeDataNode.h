#ifndef _BpTreeDataNode_H_
#define _BpTreeDataNode_H_
#include <map>
#include <string>
#include "BpTreeNode.h"

class BpTreeDataNode : public BpTreeNode
{
private:
    map <string, LoanBookData*> dataMap; // Map to store LoanBookData
    BpTreeNode* pNext;                    // Pointer to the next node
    BpTreeNode* pPrev;                    // Pointer to the previous node

public:
    // Constructor
    BpTreeDataNode() {
        pNext = NULL;
        pPrev = NULL;
    }

    // Destructor
    ~BpTreeDataNode() {

    }

    // Overridden methods from BpTreeNode
    void setNext(BpTreeNode* pN) { pNext = pN; }
    void setPrev(BpTreeNode* pN) { pPrev = pN; }
    BpTreeNode* getNext() { return pNext; }
    BpTreeNode* getPrev() { return pPrev; }

    // Overridden method to return the node type
    NodeType getNodeType() const override { return NodeType::Data; }

    // Method to insert a new key-value
    void insertDataMap(string name, LoanBookData* pN) {
        dataMap.insert(map<string, LoanBookData*>::value_type(name, pN));
    }

    // Method to delete a key-value pair
    void deleteMap(string name) {
        dataMap.erase(name);
    }

    // Overridden method to return a pointer
    map<string, LoanBookData*>* getDataMap() override { return &dataMap; }
};

#endif
