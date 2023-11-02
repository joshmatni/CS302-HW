// Authors: Ploy Wandeevong and Josh Matni (CS302 HW 4, Group 19)
// Purpose: Implementation for priorityQueue class
// Date: 10/13/2023

#include "priorityQueue.h"

template <class ItemType>
PriorityQueue<ItemType>::PriorityQueue()
{
    this->front = this->back = -1;
    this->itemCount = 0;
}

template <class ItemType>
bool PriorityQueue<ItemType>::enqueue(const ItemType& newEntry) 
{
    //! sorting smallest to largest
    bool ableToEnqueue = (this->itemCount != MAX_CAPACITY);

    if(this->isEmpty() && ableToEnqueue)
    {
        this->front = 0;
        this->back = 0;
        this->queue[this->back] = newEntry;
        this->itemCount++;
        //cout << "FIRST OF QUEUE: " << this->peekFront().getTime() << '\n';
        return true;
    }
    else if(!this->isEmpty() && ableToEnqueue)
    {
        int index = -1; // initialize with an invalid value

        for(int i = this->front; i <= this->back; i++)
        {
            if(newEntry < this->queue[i]) //  overload
            {
                index = i;
                break; 
            }
        }

        if(index == -1) // new entry is greater than all existing entries
        {
            this->back = (this->back + 1) % MAX_CAPACITY;
            this->queue[this->back] = newEntry;
        }
        else
        {
            for(int j = this->back; j >= index; j--)
            {
                this->queue[j+1] = this->queue[j];
            }
            this->queue[index] = newEntry;
            this->back = (this->back + 1) % MAX_CAPACITY;
        }

        this->itemCount++;
    }

    return ableToEnqueue;
}
