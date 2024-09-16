#pragma once
#include "LoanBookData.h"
#include <map>

// Keeping this definition outside the class
enum class NodeType {
    Index,
    Data
};

class BpTreeNode
{
private:
    BpTreeNode* pParent;               // Pointer to the parent node
    BpTreeNode* pMostLeftChild;        // Pointer to the most left child node

public:
    // Constructor
    BpTreeNode() : pParent(nullptr), pMostLeftChild(nullptr) {}

    // Virtual destructor for safe
    virtual ~BpTreeNode() = default;

    // Pure virtual function
    virtual NodeType getNodeType() const = 0;

    // Setter methods for node
    void setMostLeftChild(BpTreeNode* pNode) { pMostLeftChild = pNode; }
    void setParent(BpTreeNode* pNode) { pParent = pNode; }

    // Getter methods for node
    BpTreeNode* getParent() const { return pParent; }
    BpTreeNode* getMostLeftChild() const { return pMostLeftChild; }

    // Virtual methods for manipulating the node
    virtual void setNext(BpTreeNode* pNode) {}
    virtual void setPrev(BpTreeNode* pNode) {}
    virtual BpTreeNode* getNext() const { return nullptr; }
    virtual BpTreeNode* getPrev() const { return nullptr; }

    // Virtual methods for inserting and deleting data
    virtual void insertDataMap(const string& key, LoanBookData* pData) {}
    virtual void insertIndexMap(const string& key, BpTreeNode* pNode) {}
    virtual void deleteMap(const string& key) {}

    // Methods to get the data and index maps
    virtual map<string, BpTreeNode*>* getIndexMap() { return nullptr; }
    virtual map<string, LoanBookData*>* getDataMap() { return nullptr; }

};
