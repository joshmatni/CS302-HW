// Authors: Ploy Wandeevong and Joshua Matni
// Purpose: Binary Trees and Binary Search Trees!
// Date: 11/04/2023
#include "LinkedBTree.h"
#include <algorithm>

//PUBLIC FUNCTIONS
template<class ItemType> 
LinkedBTree<ItemType>::LinkedBTree()
{
    rootPtr = nullptr;
}
//copy constructor
template<class ItemType> 
LinkedBTree<ItemType>::LinkedBTree(const LinkedBTree& rhs)
{
    //empty tree
    if(rhs.rootPtr == nullptr)
        rootPtr = nullptr;
    else
    {
        rootPtr = new LinkedTreeNode<ItemType>(rhs.rootPtr->getItem());
        rootPtr->setLeftChildPtr(copyHelper(rhs.rootPtr->getLeftChildPtr()));
        rootPtr->setRightChildPtr(copyHelper(rhs.rootPtr->getRightChildPtr()));
    }
}

template <class ItemType>
LinkedTreeNode<ItemType>* LinkedBTree<ItemType>::copyHelper(LinkedTreeNode<ItemType>* otherTreePtr)
{
    //when we reach the end DONESSS
    if(otherTreePtr == nullptr)
        return nullptr;

    LinkedTreeNode<ItemType>* newNode = new LinkedTreeNode<ItemType>(otherTreePtr->getItem());
    newNode->setLeftChildPtr(copyHelper(otherTreePtr->getLeftChildPtr()));
    newNode->setRightChildPtr(copyHelper(otherTreePtr->getRightChildPtr()));
    return newNode;
}

template<class ItemType> 
bool LinkedBTree<ItemType>::isEmpty() const
{
    return rootPtr == nullptr;
}

template<class ItemType> 
int LinkedBTree<ItemType>::getHeight()
{
    return getHeightHelper(rootPtr);
}

template<class ItemType> 
int LinkedBTree<ItemType>::getNumberOfNodes() const
{
    return getNumberOfNodesHelper(rootPtr);
}

template<class ItemType> 
ItemType LinkedBTree<ItemType>::getRootData() const
{
    return rootPtr->getItem();
}

template<class ItemType> 
bool LinkedBTree<ItemType>::add(const ItemType& newEntry)
{
    LinkedTreeNode<ItemType>* newNode = new LinkedTreeNode<ItemType>(newEntry); // allocate new node for newEntry
    newNode->setItem(newEntry);
    newNode->setLeftChildPtr(nullptr);
    newNode->setRightChildPtr(nullptr);
    
    rootPtr = balancedAdd(rootPtr, newNode);

    return true;
}

template<class ItemType> 
bool LinkedBTree<ItemType>::remove(const ItemType& anEntry)
{
    bool isSuccessful = false;
    isSuccessful = removeValue(rootPtr, anEntry, isSuccessful);

    return isSuccessful;
}

template<class ItemType> 
void LinkedBTree<ItemType>::clear()
{
    if(isEmpty()) // case for empty tree
        return;
    else
        destroyTree(rootPtr);
    rootPtr = nullptr; // ensure tree is in empty state
}

template<class ItemType> 
bool LinkedBTree<ItemType>::contains(const ItemType& anEntry) const
{
    bool isSuccessful = false;
    findNode(rootPtr, anEntry, isSuccessful);
    return isSuccessful;
}

template<class ItemType> 
LinkedBTree<ItemType>::~LinkedBTree()
{
    clear();
}

//PROTECTED FUNCTIONS

template<class ItemType> 
int LinkedBTree<ItemType>::getHeightHelper(LinkedTreeNode<ItemType>* subTreePtr)
{
    if(subTreePtr == nullptr) // base case
        return 0;
    else
        return 1 + std::max(getHeightHelper(subTreePtr->getLeftChildPtr()), getHeightHelper(subTreePtr->getRightChildPtr()));
}

template<class ItemType> 
int LinkedBTree<ItemType>::getNumberOfNodesHelper(LinkedTreeNode<ItemType>* subTreePtr) const
{
    //base case when we reach nullptr/end of tree
    if(subTreePtr == nullptr)
    {
        return 0;
    }

    else
    {
        //add as we go down the tree, +1 for the root
        return 1 + getNumberOfNodesHelper(subTreePtr->getLeftChildPtr()) + getNumberOfNodesHelper(subTreePtr->getRightChildPtr());
    }
}

template<class ItemType> 
LinkedTreeNode<ItemType>* LinkedBTree<ItemType>::balancedAdd(LinkedTreeNode<ItemType>* subTreePtr, LinkedTreeNode<ItemType>* newNodePtr)
{
    if(subTreePtr == nullptr) // base case
        return newNodePtr;

    //case: left child > right, add to right
    if(getHeightHelper(subTreePtr->getLeftChildPtr()) > getHeightHelper(subTreePtr->getRightChildPtr()))
    {
        subTreePtr->setRightChildPtr(balancedAdd(subTreePtr->getRightChildPtr(), newNodePtr));
    }

    //case: left < right or left == right, add to left
    else 
    {
        subTreePtr->setLeftChildPtr(balancedAdd(subTreePtr->getLeftChildPtr(), newNodePtr));
    }

    return subTreePtr;
}

template<class ItemType> 
LinkedTreeNode<ItemType>* LinkedBTree<ItemType>::removeValue(LinkedTreeNode<ItemType>* subTreePtr, const ItemType target, bool& isSuccessful)
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
        
        //check if leaf
        if(subTreePtr->isLeaf())
        {
            //deallocate node
            delete subTreePtr;
            subTreePtr = nullptr;

            return subTreePtr;
        }

        //not a leaf, change structure w moveValuesUp()
        else
        {
            subTreePtr = this->MoveValuesUpTree(subTreePtr);
            return subTreePtr;
        }
    }

    //otherwise, continue looking
    else
    {
        //look left
        subTreePtr->setLeftChildPtr(removeValue(subTreePtr->getLeftChildPtr(), target, isSuccessful));

        //if not found, look right
        if(!isSuccessful)
        {
            subTreePtr->setRightChildPtr(removeValue(subTreePtr->getRightChildPtr(), target, isSuccessful));
        }
        
        return subTreePtr;
    }
}

template<class ItemType> 
LinkedTreeNode<ItemType>* LinkedBTree<ItemType>::MoveValuesUpTree(LinkedTreeNode<ItemType>* subTreePtr)
{
    if(subTreePtr == nullptr) // nothing to move up
        return subTreePtr;

    // in order successor
    // starting from right child of subTree go down to left most node
    LinkedTreeNode<ItemType>* currentChild = subTreePtr->getRightChildPtr();

    while(currentChild != nullptr)
    {
        if(currentChild->getLeftChildPtr() != nullptr)
            currentChild = currentChild->getLeftChildPtr();
        else
            break; // found in order successor
    }

    subTreePtr->setItem(currentChild->getItem()); // move value up
    bool isSuccessful = false;

    // remove in order successor
    LinkedTreeNode<ItemType>* newRightChild = removeValue(subTreePtr->getRightChildPtr(), currentChild->getItem(), isSuccessful);

    if(isSuccessful) // update rightChild
        subTreePtr->setRightChildPtr(newRightChild);
    
    return subTreePtr;
}

template<class ItemType> 
LinkedTreeNode<ItemType>* LinkedBTree<ItemType>::findNode(LinkedTreeNode<ItemType>* subTreePtr, const ItemType& target, bool& isSuccessful) const
{
    //if we can't find it, return null, not successful
    if(subTreePtr == nullptr)
    {
        isSuccessful = 0;
        return nullptr;
    }

    //if we find it, return ptr
    else if(subTreePtr->getItem() == target)
    {
        isSuccessful = 1;
        return subTreePtr;
    }

    //search left first
    else
    {
        return findNode(subTreePtr->getLeftChildPtr(), target, isSuccessful);

        //if unsuccessful (subtreePtr == nullptr), search right next
        if(!subTreePtr)
        {
            return findNode(subTreePtr->getRightChildPtr(), target, isSuccessful);
        }
    }
}

template<class ItemType> 
void LinkedBTree<ItemType>::destroyTree(LinkedTreeNode<ItemType>* subTreePtr) // subTree = current node
{
    if(subTreePtr == nullptr) // base case
        return;

    else //! must delete children first before deleting the current node
    {
        destroyTree(subTreePtr->getLeftChildPtr()); // delete all nodes in left subTree
        destroyTree(subTreePtr->getRightChildPtr()); // delete all nodes in right subTree
        delete subTreePtr; // delete current node
    }
}
