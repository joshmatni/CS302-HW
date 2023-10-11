#include "train.h"

// Implementation of the Train class template which represents a customizable Train transporter
// Handles cargo management, movement, and train state-related functionalities

template <class T>
Train<T>::Train()
{
    total_weight = 1;
    numCargo = 1;
}

template <class T>
Train<T>::Train(T* newItems, int newNumItems, float newTotalWeight)
{
    total_weight = newTotalWeight; 
    numCargo = newNumItems;
    for(int i = 0; i < newNumItems; i++)
    {
        items[i] = newItems[i];
    }
}

template <class T>
Train<T>::Train(const Train &rhs)
{
    total_weight = rhs.total_weight;
    numCargo = rhs.numCargo;
    for(int i = 0; i < rhs.numCargo; i++)
    {
        items[i] = rhs.items[i];
    }
}
template <class T>
float Train<T>::getTotalWeight() const
{
    return total_weight;
}

template <class T>
void Train<T>::setTotalWeight(const float newTotalWeight)
{
    total_weight = newTotalWeight;
}

template <class T>
void Train<T>::loadItemToTransporter(T newItemToLoad) 
{
    items[numCargo] = newItemToLoad; 
    numCargo++; 
    total_weight += newItemToLoad.getWeight();
}

template <class T>
void Train<T>::moving() const
{
    cout << "We have reached the next stop!" << endl;
}

template <class T>
T* Train<T>::getItems()
{
    return items;
}

template <class T>
void Train<T>::unloadItemFromTransporter() //last inputted item
{
   items[numCargo-1] = T(); // fill withempty object
   numCargo--;
}

template <class T>
void Train<T>::emptyAllItems()
{
    // or you can just repeated call unload item
    for(int i = 0; i < numCargo; i++)
    {
        items[i] = T();
    }
    numCargo = 0;
}

template <class T>
bool Train<T>::isEmpty() const 
{
    if(numCargo == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <class T>
int Train<T>::getNumItems() const
{
    return numCargo;
}


