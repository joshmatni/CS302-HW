#include "linkedStack.h"

template <class ItemType>
LinkedStack<ItemType>::LinkedStack()
{
    top = nullptr;
}

template <class ItemType>
LinkedStack<ItemType>::LinkedStack(const LinkedStack<ItemType> &rhs)
{
    top = nullptr;
    Node<ItemType>* currentPtr = rhs.top; // to traverse through stack
    Node<ItemType>* newStackPtr = nullptr; // keeps track of prev node added

    while(currentPtr != nullptr)
    {
        Node<ItemType>* newNode = new Node<ItemType>(currentPtr->getItem()); // allocate new node and its item

        if(top == nullptr) // case for empty stack
        {
            top = newNode;
        }
        else
        {
            newStackPtr->setNext(newNode);
        }

        newStackPtr = newNode; // update newStackPtr
        currentPtr = currentPtr->getNext(); // move to next node in stack

    }
}

template <class ItemType>
bool LinkedStack<ItemType>::isEmpty() const
{
    return top == nullptr; 
}

template <class ItemType>
bool LinkedStack<ItemType>::push(const ItemType& newEntry)
{
    Node<ItemType>* temp = new Node<ItemType>(newEntry); // allocates new node for newEntry
    
    if(temp != nullptr)
    {
        temp->setNext(top); // temp points to the prev top
        top = temp;
        return true;
    }
    return false;
}

template <class ItemType>
bool LinkedStack<ItemType>::pop()
{
    bool ableToPop = (top != nullptr);

    if(ableToPop)
    {
        Node<ItemType>* temp = top; // holds node to delete
        top = top->getNext(); // set top to node below
        delete temp;
        return true;
    }
    return false;
}

template <class ItemType>
ItemType LinkedStack<ItemType>::peek() const
{
    bool ableToPeek = (top != nullptr);
    if(ableToPeek)
    {
        return top->getItem(); // return only item
    }
    throw "Empty Stack!";
}

template <class ItemType>
LinkedStack<ItemType>::~LinkedStack()
{
    Node<ItemType>* currentPtr = top;

    while(currentPtr != nullptr)
    {
        Node<ItemType>* nextNode = currentPtr->getNext(); // save address of nextNode
        delete currentPtr; // delete current node 
        currentPtr = nextNode;
    }
    top = nullptr;
}