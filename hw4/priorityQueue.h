// Authors: Ploy Wandeevong and Josh Matni (CS302 HW 4, Group 19)
// Purpose: PriorityQueue Declarations
// Date: 10/13/2023

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "arrayQueue.h"

template <class ItemType>
class PriorityQueue: public ArrayQueue<ItemType>
{
    public:
        PriorityQueue();
        bool enqueue(const ItemType&) override; // sort the customers (use operator)
        //bool dequeue() override;
        // ItemType peekFront() const override;
        int getItemCount();
};
#include "priorityQueue.cpp"
#endif
