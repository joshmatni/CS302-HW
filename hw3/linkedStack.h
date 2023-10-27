#ifndef LINKEDSTACK_H
#define LINKEDSTACK_H

#include "stack.h"
#include "node.h"
#include <iostream>
using namespace std;

template <class ItemType>
class LinkedStack: public StackInterface<ItemType>
{
    Node<ItemType>* top; // top = headptr

    public:
        LinkedStack();
        LinkedStack(const LinkedStack<ItemType>&);
        virtual bool isEmpty() const override; 
        virtual bool push(const ItemType& newEntry) override; 
        virtual bool pop() override; 
        virtual ItemType peek() const override; 
        virtual ~LinkedStack() override;
};
#include "linkedStack.cpp"
#endif