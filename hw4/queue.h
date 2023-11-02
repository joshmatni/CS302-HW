// Authors: Ploy Wandeevong and Josh Matni (CS302 HW 4, Group 19)
// Purpose: Queue Interface
// Date: 10/13/2023

#ifndef QUEUE_INTERFACE 
#define QUEUE_INTERFACE 

template<class ItemType> 
class QueueInterface { 
public: 
    virtual bool isEmpty() const = 0; 
    virtual bool enqueue(const ItemType& newEntry) = 0; 
    virtual bool dequeue() = 0; 
    virtual ItemType peekFront() const = 0; 
    
    virtual ~QueueInterface() { } 
};  
#endif
