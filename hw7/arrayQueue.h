// REFERENCED FROM CS302 GITHUB HOMEWORK SOLUTIONS

#ifndef ARRAY_QUEUE 
#define ARRAY_QUEUE

#include "queue.h"

template<class ItemType> 
class ArrayQueue: public QueueInterface<ItemType> {
protected:
    static const int DEFAULT_CAPACITY = 100;
    int frontIndex, backIndex, itemCount;
    ItemType items[DEFAULT_CAPACITY - 1];
public: 
    ArrayQueue();

    bool isEmpty() const; 
    bool enqueue(const ItemType& newEntry); 
    bool dequeue(); 
    ItemType peekFront() const; 

    ~ArrayQueue() { } 
};  
#include "arrayQueue.cpp"
#endif