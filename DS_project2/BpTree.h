#ifndef _BpTree_H_
#define _BpTree_H_

#include "BpTreeDataNode.h"
#include "BpTreeIndexNode.h"
#include "LoanBookData.h"
#include <fstream>
#include <iostream>

class BpTree 
{
private:
    BpTreeNode* root;        // Root 
    int order;               // Maximum number 
    ofstream* fout;          // Output file stream 

public:
    // Constructor
    BpTree(ofstream *fout, int order = 3) 
    {
        root = NULL;
        this->order = order;
        this->fout = fout;
    }

    // Destructor
    ~BpTree()
    {
        deleteTree(root);
        root = nullptr;
    }

    bool Insert(LoanBookData* newData);                     // insert new data
    bool excessDataNode(BpTreeNode* pDataNode);             // Checks a data node
    bool excessIndexNode(BpTreeNode* pIndexNode);           // Checks an index node
    void splitDataNode(BpTreeNode* pDataNode);              // Splits a data node 
    void splitIndexNode(BpTreeNode* pIndexNode);            // Splits an index node 
    BpTreeNode* getRoot() { return root; }                  // Gets the root 
    BpTreeNode* searchDataNode(const string& name);         // Searches for a data node

    bool searchBook(string name);                           // Searches for book
    bool searchRange(string start, string end);             // Searches in a given range

    bool isLeafNode(BpTreeNode* node);                      // Checks a given node
    BpTreeNode* searchLeafNode(const string& key);          // Searches for the leaf node

    LoanBookData* getBookDetails(const string& name);       // Gets details of a book

    // Method to delete the tree
    void deleteTree(BpTreeNode* node) 
    {
        if (node != nullptr) {
            // Recursively delete
            if (auto indexNode = dynamic_cast<BpTreeIndexNode*>(node)) {
                for (auto& child : *indexNode->getIndexMap()) {
                    deleteTree(child.second);
                }
            }

            // delete the node
            delete node;
        }
    }
    
    // Method to get the leftmost data node
    BpTreeNode* getLeftmostDataNode() 
    {
        BpTreeNode* node = root; // Start at the root node
        if (!node) return nullptr; 

        // Traverse
        while (node->getNodeType() == NodeType::Index) {
            node = node->getMostLeftChild();
        }

        // At the end of the loop
        return dynamic_cast<BpTreeDataNode*>(node); // Cast to BpTreeDataNode type
    }
};

#endif
