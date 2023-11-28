// Authors: Ploy Wandeevong and Joshua Matni
// Purpose: Binary Trees and Binary Search Trees!
// Date: 11/04/2023

#ifndef LINKED_B_TREE
#define LINKED_B_TREE

#include "tree.h"
#include "linkedtreenode.h"

template<class ItemType> 
class LinkedBTree : public TreeInterface<ItemType>
{
    private:
        LinkedTreeNode<ItemType>* rootPtr;

    public: //! from tree.h
        LinkedBTree();
        LinkedBTree(const LinkedBTree& rhs);
        LinkedTreeNode<ItemType>* copyHelper(LinkedTreeNode<ItemType>* otherTreePtr);
        bool isEmpty() const override;
        int getHeight() override;
        int getNumberOfNodes() const override; 
        ItemType getRootData() const override;
        bool add(const ItemType& newEntry) override;
        bool remove(const ItemType& anEntry) override;
        void clear() override; 
        bool contains(const ItemType& anEntry) const override;
        ~LinkedBTree() override;

    protected:
        int getHeightHelper(LinkedTreeNode<ItemType>* subTreePtr);
        int getNumberOfNodesHelper(LinkedTreeNode<ItemType>* subTreePtr) const;
        LinkedTreeNode<ItemType>* balancedAdd(LinkedTreeNode<ItemType>* subTreePtr, LinkedTreeNode<ItemType>* newNodePtr);
        LinkedTreeNode<ItemType>* removeValue(LinkedTreeNode<ItemType>* subTreePtr, const ItemType target, bool& isSuccessful);
        LinkedTreeNode<ItemType>* MoveValuesUpTree(LinkedTreeNode<ItemType>* subTreePtr);
        LinkedTreeNode<ItemType>* findNode(LinkedTreeNode<ItemType>* subTreePtr, const ItemType& target, bool& isSuccessful) const;
        void destroyTree(LinkedTreeNode<ItemType>* subTreePtr);
};

#include "LinkedBTree.cpp"
#endif