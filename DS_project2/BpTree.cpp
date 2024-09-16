#include "BpTree.h"
#include <cmath>


// Function to insert new data
bool BpTree::Insert(LoanBookData* newData) 
{
    // Check if the data already exists
    if (searchDataNode(newData->getName()) != nullptr) {
        // Duplicate data cannot be inserted
        return false;
    }

    // Find the appropriate leaf node
    BpTreeDataNode* leafNode = dynamic_cast<BpTreeDataNode*>(searchLeafNode(newData->getName()));
    if (leafNode == nullptr) {
        //create a new leaf node
        leafNode = new BpTreeDataNode();
        root = leafNode; // The new node becomes the root
    }

    // Insert the data
    leafNode->insertDataMap(newData->getName(), newData);

    // Check and handle node overflow
    BpTreeNode* currentNode = leafNode;

    return true;
}


// Function to find the leaf node
BpTreeNode* BpTree::searchLeafNode(const string& key) {
    BpTreeNode* currentNode = root;

    // Traverse from the root 
    while (currentNode != nullptr && !isLeafNode(currentNode)) {
        BpTreeNode* nextNode = nullptr;
        map<string, BpTreeNode*>* indexMap = currentNode->getIndexMap();
        auto it = indexMap->lower_bound(key);

        // Determine the next node
        if (it == indexMap->end()) {
            nextNode = (--it)->second;
        } else if (it == indexMap->begin()) {
            nextNode = currentNode->getMostLeftChild();
        } else {
            nextNode = (--it)->second;
        }

        currentNode = nextNode;
    }

    // Return the found leaf node
    return currentNode;
}

// to check if a node is a leaf node
bool BpTree::isLeafNode(BpTreeNode* node) {
    return node->getMostLeftChild() == nullptr;
}



// to check if a data node has exceeded its capacity
bool BpTree::excessDataNode(BpTreeNode* pDataNode) {
    if (pDataNode->getDataMap()->size() > order - 1) return true;//order is equal to the number of elements 
    else return false;
}



// to check if an index node has exceeded its capacity
bool BpTree::excessIndexNode(BpTreeNode* pIndexNode) {
    if (pIndexNode->getIndexMap()->size() > order - 1)return true;//order is equal to the number of elements 
    else return false;
}


// to split an overflowing data node
void BpTree::splitDataNode(BpTreeNode* pDataNode) {
    // Casting the generic node
    BpTreeDataNode* dataNode = dynamic_cast<BpTreeDataNode*>(pDataNode);

    // Calculating
    int splitIndex = dataNode->getDataMap()->size() / 2;

    // Creating new nodes
    BpTreeDataNode* left = new BpTreeDataNode();
    BpTreeDataNode* right = new BpTreeDataNode();

    // Splitting the data map
    auto& mapData = *(dataNode->getDataMap());
    auto it = mapData.begin();
    for (int i = 0; i < splitIndex; ++i, ++it) {
        left->insertDataMap(it->first, it->second);
    }
    string middleKey = it->first;
    ++it;
    while (it != mapData.end()) {
        right->insertDataMap(it->first, it->second);
        it++;
    }

    // Handling the parent node
    BpTreeNode* parent = pDataNode->getParent();
    if (parent == nullptr) {
        parent = new BpTreeIndexNode();
        root = parent;
        left->setParent(parent);
        right->setParent(parent);
        static_cast<BpTreeIndexNode*>(parent)->insertIndexMap(middleKey, right);
        static_cast<BpTreeIndexNode*>(parent)->setMostLeftChild(left);
    } else {
        left->setParent(parent);
        right->setParent(parent);
        static_cast<BpTreeIndexNode*>(parent)->insertIndexMap(middleKey, right);
    }

    // Splitting the parent index node if necessary
    if (excessIndexNode(parent)) {
        splitIndexNode(parent);
    }

    // Deleting the old data node
    delete pDataNode;
}



void BpTree::splitIndexNode(BpTreeNode* pIndexNode) {
    int splitPoint = static_cast<int>(ceil((order - 1) / 2.0))+1;

    // Creating new index node.
    auto newIdxNode = new BpTreeIndexNode();

    // Getting the map
    auto& indexMap = *static_cast<BpTreeIndexNode*>(pIndexNode)->getIndexMap();

    // Iterator to the split point
    auto it = indexMap.begin();
    std::advance(it, splitPoint-1);
    string middleKey = it->first; 

    for (++it; it != indexMap.end();) {
        newIdxNode->insertIndexMap(it->first, it->second);
        it->second->setParent(newIdxNode);
        it = indexMap.erase(it); // Erase and advance the iterator.
    }

    // Parent handling
    BpTreeNode* parent = pIndexNode->getParent();
    if (parent == nullptr) {
        // If no parent
        parent = new BpTreeIndexNode();
        root = parent;
        pIndexNode->setParent(parent);
        newIdxNode->setParent(parent);

        // The old root 
        static_cast<BpTreeIndexNode*>(parent)->setMostLeftChild(pIndexNode);
    }

    // Inserting the middle key 
    static_cast<BpTreeIndexNode*>(parent)->insertIndexMap(middleKey, newIdxNode);

    // Setting up sibling pointers
    newIdxNode->setPrev(pIndexNode);
    newIdxNode->setNext(pIndexNode->getNext());
    pIndexNode->setNext(newIdxNode);
    if (newIdxNode->getNext() != nullptr) {
        newIdxNode->getNext()->setPrev(newIdxNode);
    }

    // If the parent is full
    if (excessIndexNode(parent)) {
        splitIndexNode(parent);
    }
}

BpTreeNode* BpTree::searchDataNode(const string& name) {
    BpTreeNode* current = root;

    // If the tree is empty
    if (!current) return nullptr;

    while (current) {
        // Check if the current node
        if (isLeafNode(current)) {
            // Cast the current node
            auto dataNode = dynamic_cast<BpTreeDataNode*>(current);
            if (dataNode) {
                // Search for the name in the data map
                auto it = dataNode->getDataMap()->find(name);
                if (it != dataNode->getDataMap()->end()) {
                    // Found the name in this data node
                    return current;
                } else {
                    // Name not found in this leaf node
                    return nullptr;
                }
            } else {
                throw std::runtime_error("100");
            }
        } else {
            // find the next child to follow
            auto indexNode = dynamic_cast<BpTreeIndexNode*>(current);
            if (indexNode) {
                // Find the child pointer 
                auto it = indexNode->getIndexMap()->upper_bound(name);
                if (it == indexNode->getIndexMap()->begin()) {
                    //  go to the leftmost child
                    current = indexNode->getMostLeftChild();
                } else {
                    // Go to the child pointer
                    --it;
                    current = it->second;
                }
            } else {
                // if the tree structure is correct
                throw std::runtime_error("100");
            }
        }
    }

    // Name not found
    return nullptr;
}


//check if a specific book exists
bool BpTree::searchBook(string name) {
    // Search for the data node
    BpTreeNode* dataNode = searchDataNode(name);

    // Return true if the data node is found
    return (dataNode != nullptr);
}

// check if there are any books
bool BpTree::searchRange(string start, string end) {
    // Find the leaf node
    BpTreeNode* currentNode = searchLeafNode(start);

    // Iterate through the leaf nodes
    while (currentNode != nullptr) {
        // Cast the current node
        auto dataNode = dynamic_cast<BpTreeDataNode*>(currentNode);
        if (!dataNode) {
            break; 
        }

        // Iterate through the entries in the data node
        for (const auto& entry : *dataNode->getDataMap()) {
            string key = entry.first;

            if (key >= start && key < end) {
                return true; // Found at least one boo
            } else if (key >= end) {
                break; 
            }
        }

        // Move to the next data node 
        currentNode = currentNode->getNext();
    }
    return false; 
}


// to get the details of a book by name
LoanBookData* BpTree::getBookDetails(const string& name) 
{
    BpTreeNode* dataNode = searchDataNode(name);
    if (dataNode) {
        auto dataMap = dynamic_cast<BpTreeDataNode*>(dataNode)->getDataMap();
        auto it = dataMap->find(name);
        if (it != dataMap->end()) {
            return dynamic_cast<LoanBookData*>(it->second);
        }
    }
    return nullptr; // if there is null book
}

