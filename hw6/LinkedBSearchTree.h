// Authors: Ploy Wandeevong and Joshua Matni
// Purpose: Binary Trees and Binary Search Trees!
// Date: 11/04/2023

#ifndef LINKED_B_SEARCH_TREE
#define LINKED_B_SEARCH_TREE

#include "LinkedBTree.h"

template<class ItemType> 
class LinkedBSearchTree : public LinkedBTree<ItemType>
{
    private:
        LinkedTreeNode<ItemType>* rootPtr;

    protected:
        LinkedTreeNode<ItemType>* placeNode(LinkedTreeNode<ItemType>* subTreePtr, LinkedTreeNode<ItemType>* newNodePtr);
        LinkedTreeNode<ItemType>* removeValue(LinkedTreeNode<ItemType>* subTreePtr, const ItemType target, bool& isSuccessful);
        LinkedTreeNode<ItemType>* removeNode(LinkedTreeNode<ItemType>* nodePtr);
        LinkedTreeNode<ItemType>* removeLeftmostNode(LinkedTreeNode<ItemType>* nodePtr, ItemType inorderSuccessor);
        LinkedTreeNode<ItemType>* findNode(LinkedTreeNode<ItemType>* treePtr, const ItemType& target) const;

        void preorder(void visit(ItemType), LinkedTreeNode<ItemType>* treePtr) const;
        void inorder(void visit(ItemType), LinkedTreeNode<ItemType>* treePtr) const;
        void postorder(void visit(ItemType), LinkedTreeNode<ItemType>* treePtr) const;
    
    public:
        LinkedBSearchTree();
        bool isEmpty() const;
        int getHeight();
        int getNumberOfNodes() const;
        ItemType getRootData() const;
        bool add(const ItemType& newData);
        bool remove(const ItemType& data);
        void clear();
        bool contains(const ItemType& anEntry) const;
        void preorderTraverse(void visit(ItemType)) const;
        void inorderTraverse(void visit(ItemType)) const;
        void postorderTraverse(void visit(ItemType)) const;
        ~LinkedBSearchTree();
};

#include "LinkedBSearchTree.cpp"
#endif