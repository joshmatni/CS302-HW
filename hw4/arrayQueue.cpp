// Authors: Ploy Wandeevong and Josh Matni (CS302 HW 4, Group 19)
// Purpose: ArrayQueue Implementation
// Date: 10/13/2023

#include "arrayQueue.h"
 
template <class ItemType>
ArrayQueue<ItemType>::ArrayQueue()
{
    front = back = -1;
    itemCount = 0;
}

template <class ItemType>
ArrayQueue<ItemType>::ArrayQueue(const ArrayQueue &rhs)
{
    front = rhs.front;
    back = rhs.back;
    itemCount = rhs.itemCount;

    for(int i = 0; i < rhs.itemCount; i++)
    {
        queue[i] = rhs.queue[i];
    }
}

template <class ItemType>
bool ArrayQueue<ItemType>::isEmpty() const
{
    return itemCount == 0;
}

template <class ItemType>
bool ArrayQueue<ItemType>::enqueue(const ItemType& newEntry)
{
    bool ableToEnqueue = (itemCount != MAX_CAPACITY);

    // edge case for empty queue
    if(isEmpty())
    {
        front = back = 0;
        queue[back] = newEntry;
        itemCount++; 
    }

    //increment back
    else if(ableToEnqueue)
    {
        back = (back + 1) % MAX_CAPACITY;
        queue[back] = newEntry;
        itemCount++;  // handles wrap around
    }

    return ableToEnqueue;
}

template <class ItemType>
bool ArrayQueue<ItemType>::dequeue()
{
    bool ableToDequeue = !isEmpty();

    if(ableToDequeue)
    {
        front = (front + 1) % MAX_CAPACITY; // handles wrap around
        itemCount--;
    }

    return ableToDequeue;
}

template <class ItemType>
ItemType ArrayQueue<ItemType>::peekFront() const 
{
    if(isEmpty())
    {
        throw "Queue is empty!";
    }
    
    return queue[front];
}

template <class ItemType>
ArrayQueue<ItemType>::~ArrayQueue() // set items to default value ?
{
    front = back = -1;
    itemCount = 0;
}