#ifndef _BPTREEINDEXNODE_H_
#define _BPTREEINDEXNODE_H_

#include "BpTreeNode.h"
#include <map>
#include <string>

class BpTreeIndexNode : public BpTreeNode {
private:
    map <string, BpTreeNode*> indexMap; // child nodes with string keys

public:
    // Constructor
    BpTreeIndexNode() {};

    // Destructor
    ~BpTreeIndexNode() {};

    // Method to insert a child node
    void insertIndexMap(string name, BpTreeNode* pN) {
        indexMap.insert(map<string, BpTreeNode*>::value_type(name, pN));
    }

    // Method to delete a child node
    void deleteMap(string name) {
        indexMap.erase(name);
    }

    //to return the node type 
    NodeType getNodeType() const override { return NodeType::Index; }

    //to return a pointer to the index map
    map <string, BpTreeNode*>* getIndexMap() override { return &indexMap; }
};

#endif
