#include "LinkedBSearchTree.h"
// Authors: Ploy Wandeevong and Joshua Matni
// Purpose: Binary Trees and Binary Search Trees!
// Date: 11/04/2023

//PUBLIC FUNCTIONS
template<class ItemType> 
int LinkedBSearchTree<ItemType>::getHeight()
{
    return this->getHeightHelper(rootPtr);
}

template<class ItemType> 
LinkedBSearchTree<ItemType>::LinkedBSearchTree()
{
    rootPtr = nullptr;
}

template<class ItemType> 
bool LinkedBSearchTree<ItemType>::isEmpty() const
{
    return rootPtr == nullptr;
}

template<class ItemType> 
bool LinkedBSearchTree<ItemType>::add(const ItemType& newData)
{
    LinkedTreeNode<ItemType>* newNode = new LinkedTreeNode<ItemType>(newData); // allocate new node for newEntry
    newNode->setItem(newData);
    newNode->setLeftChildPtr(nullptr);
    newNode->setRightChildPtr(nullptr);
    
    rootPtr = placeNode(rootPtr, newNode);

    return true;
}

template<class ItemType> 
void LinkedBSearchTree<ItemType>::clear()
{
    if(isEmpty()) // case for empty tree
        return;
    else
        this->destroyTree(rootPtr);
    rootPtr = nullptr; // ensure tree is in empty state
}

template<class ItemType> 
ItemType LinkedBSearchTree<ItemType>::getRootData() const
{
    return rootPtr->getItem();
}

template<class ItemType> 
int LinkedBSearchTree<ItemType>::getNumberOfNodes() const
{
    return this->getNumberOfNodesHelper(rootPtr);
}

//do we need to
template<class ItemType> 
bool LinkedBSearchTree<ItemType>::remove(const ItemType& data)
{
    bool isSuccessful = false;
    isSuccessful = removeValue(rootPtr, data, isSuccessful);
    return isSuccessful;
}

template<class ItemType> 
bool LinkedBSearchTree<ItemType>::contains(const ItemType& anEntry) const
{
    LinkedTreeNode<ItemType>* found = findNode(rootPtr, anEntry);

    if(found != nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<class ItemType> 
void LinkedBSearchTree<ItemType>::preorderTraverse(void visit(ItemType)) const
{
    preorder(visit, rootPtr);
}

template<class ItemType> 
void LinkedBSearchTree<ItemType>::inorderTraverse(void visit(ItemType)) const
{
    inorder(visit, rootPtr);
}

template<class ItemType> 
void LinkedBSearchTree<ItemType>::postorderTraverse(void visit(ItemType)) const
{
    postorder(visit, rootPtr);
}

template<class ItemType> 
LinkedBSearchTree<ItemType>::~LinkedBSearchTree()
{
    clear();
}


//PROTECTED FUNCTIONS

template<class ItemType> 
LinkedTreeNode<ItemType>* LinkedBSearchTree<ItemType>::placeNode(LinkedTreeNode<ItemType>* subTreePtr, LinkedTreeNode<ItemType>* newNodePtr)
{
    if(subTreePtr == nullptr) // base case
        return newNodePtr;

    //if item is greater, place to the right
    if(subTreePtr->getItem() < newNodePtr->getItem())
    {
        subTreePtr->setRightChildPtr(placeNode(subTreePtr->getRightChildPtr(), newNodePtr));
    }

    else 
    {
        subTreePtr->setLeftChildPtr(placeNode(subTreePtr->getLeftChildPtr(), newNodePtr));
    }

    return subTreePtr;
}

template<class ItemType> 
LinkedTreeNode<ItemType>* LinkedBSearchTree<ItemType>::removeValue(LinkedTreeNode<ItemType>* subTreePtr, const ItemType target, bool& isSuccessful)
{
    //not successful, nothing here
    if(subTreePtr == nullptr)
    {
        isSuccessful = 0;
        return subTreePtr;
    }

    //found item!!! SUCESS
    if(subTreePtr->getItem() == target)
    {
        isSuccessful = 1;
        subTreePtr = removeNode(subTreePtr);

        return subTreePtr;
    }

    //otherwise, continue looking
    else
    {
        //if target > ptr, go right
        if(target > subTreePtr->getItem())
        subTreePtr->setRightChildPtr(removeValue(subTreePtr->getRightChildPtr(), target, isSuccessful));

        //otherwise, go left
        else
        {
            subTreePtr->setLeftChildPtr(removeValue(subTreePtr->getLeftChildPtr(), target, isSuccessful));
        }
        
        return subTreePtr;
    }
}

template<class ItemType> 
LinkedTreeNode<ItemType>* LinkedBSearchTree<ItemType>::removeNode(LinkedTreeNode<ItemType>* nodePtr)
{
    //3 CASES: node is a leaf, has 1 child, or has 2 children

    //LEAF CASE
    if(nodePtr->isLeaf())
    {
        delete nodePtr;
        nodePtr = nullptr;
    }

    //ONE CHILD CASES
    //one left child
    else if(nodePtr->getLeftChildPtr() && !nodePtr->getRightChildPtr())
    {
        //save item in new node
        LinkedTreeNode<ItemType>* newNode = new LinkedTreeNode<ItemType>();
        newNode->setItem(nodePtr->getLeftChildPtr()->getItem());

        //deallocate node
        nodePtr->setLeftChildPtr(nullptr);
        delete nodePtr;
        nodePtr = nullptr;

        //return child to be swapped
        return newNode;
    }

    //if node has only a right child
    else if(!nodePtr->getLeftChildPtr() && nodePtr->getRightChildPtr())
    {
        //save item in new node
        LinkedTreeNode<ItemType>* newNode = new LinkedTreeNode<ItemType>();
        newNode->setItem(nodePtr->getRightChildPtr()->getItem());

        //deallocate child
        nodePtr->setRightChildPtr(nullptr);
        delete nodePtr;
        nodePtr = nullptr;

        //return child to be swapped
        return newNode;
    }

    //TWO CHILD CASE
    else if(nodePtr->getLeftChildPtr() && nodePtr->getRightChildPtr())
    {
        //get leftmost node of right child
        LinkedTreeNode<ItemType>* newNode = new LinkedTreeNode<ItemType>();
        newNode = removeLeftmostNode(nodePtr, nodePtr->getRightChildPtr()->getItem());

        //deallocate node to delete
        delete nodePtr;
        nodePtr = nullptr;

        return newNode;
    }
    return nodePtr;
}

template<class ItemType> 
LinkedTreeNode<ItemType>* LinkedBSearchTree<ItemType>::removeLeftmostNode(LinkedTreeNode<ItemType>* nodePtr, ItemType inorderSuccessor)
{
    // find inOrder Successor 
    if(nodePtr->getLeftChildPtr() == nullptr) // found successor 
    {
        inorderSuccessor = nodePtr->getItem();
        
        // case if successor has right child
        if(nodePtr->getRightChildPtr() != nullptr) 
            return nodePtr->getRightChildPtr(); // node will replace the node being removed

        return nodePtr;
    }

    else
    {
        nodePtr->setLeftChildPtr(removeLeftmostNode(nodePtr->getLeftChildPtr(), inorderSuccessor)); // traverse left
        return nodePtr;
    }
}


template<class ItemType> 
LinkedTreeNode<ItemType>* LinkedBSearchTree<ItemType>::findNode(LinkedTreeNode<ItemType>* treePtr, const ItemType& target) const
{

    // base case
    if(treePtr == nullptr)
    {
        return nullptr;
    }

    else if(treePtr->getItem() == target)
    {
        // if target is at current pointer, return pointer; is successful
        return treePtr;
    }

    //less than, traverse left
    else if(target < treePtr->getItem())
    {
        return findNode(treePtr->getLeftChildPtr(), target);
    }
    
    //greater than, traverse right
    else
    {
        return findNode(treePtr->getRightChildPtr(), target);
    }

}


template<class ItemType> 
void LinkedBSearchTree<ItemType>::preorder(void visit(ItemType), LinkedTreeNode<ItemType>* treePtr) const
{   // TESLA DUNN

    // base case
    if(treePtr != nullptr)
    {
        visit(treePtr->getItem()); // visit current Node
        preorder(visit, treePtr->getLeftChildPtr()); // traverse left subtree
        preorder(visit, treePtr->getRightChildPtr()); // traverse right subtree
    }
}

template<class ItemType> 
void LinkedBSearchTree<ItemType>::inorder(void visit(ItemType), LinkedTreeNode<ItemType>* treePtr) const
{
    if(treePtr != nullptr)
    {
        inorder(visit, treePtr->getLeftChildPtr());
        ItemType theItem = treePtr->getItem();
        visit(theItem);
        inorder(visit, treePtr->getRightChildPtr());
    }
}

template<class ItemType> 
void LinkedBSearchTree<ItemType>::postorder(void visit(ItemType), LinkedTreeNode<ItemType>* treePtr) const
{
    // base case
    if(treePtr != nullptr)
    {
        postorder(visit, treePtr->getLeftChildPtr()); // get to leftmost child
        postorder(visit, treePtr->getRightChildPtr()); // get to rightmost child
        visit(treePtr->getItem()); // visit the item
    }
}


