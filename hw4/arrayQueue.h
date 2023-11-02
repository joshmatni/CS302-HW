// Authors: Ploy Wandeevong and Josh Matni (CS302 HW 4, Group 19)
// Purpose: ArrayQueue Header File
// Date: 10/13/2023

#ifndef ARRAYQUEUE_H
#define ARRAYQUEUE_H

#include "queue.h"
#include <iostream>
using namespace std;
#define MAX_CAPACITY 50

template <class ItemType>
class ArrayQueue: public QueueInterface<ItemType>
{
    protected:
        ItemType queue[MAX_CAPACITY];
        int front, back, itemCount;

    public:
        ArrayQueue();
        ArrayQueue(const ArrayQueue&);
        bool isEmpty() const override; 
        virtual bool enqueue(const ItemType& newEntry) override; // added virtual (for Priority queue)
        bool dequeue() override;  
        ItemType peekFront() const override; 
        ~ArrayQueue() override;
};
#include "arrayQueue.cpp"
#endif