#include "bus.h"

// Defines a templated Bus class, specialized for transporting people with specific functionalities like fare calculation
// Incorporates features for sorting passengers based on their height and managing bus fare

template <class T>
Bus<T>::Bus()
{
    numPeople = 1;
    busFare = 1;
}

template <class T>
Bus<T>::Bus(T* newPeople, int newNumPeople, float newFare)
{
    numPeople = newNumPeople;
    busFare = newFare;
    for(int i = 0; i < newNumPeople; i++)
    {
        items[i] = newPeople[i];
    }
}

template <class T>
Bus<T>::Bus(const Bus &rhs)
{
    numPeople = rhs.numPeople;
    busFare = rhs.fare;
    for(int i = 0; i < rhs.numPeople; i++)
    {
        items[i] = rhs.items[i];
    }
}

template <class T>
T* Bus<T>::getItems()
{
    return items;
}

template <class T>
void Bus<T>::unloadItemFromTransporter() //last inputted item
{
   items[numPeople-1] = T(); //empty object
   numPeople--;
}

template <class T>
void Bus<T>::emptyAllItems()
{
    for(int i = 0; i < numPeople; i++)
    {
        items[i] = T(); // empty object
    }
    numPeople = 0;
}

template <class T>
bool Bus<T>::isEmpty() const 
{
    if(numPeople == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <class T>
void Bus<T>::loadItemToTransporter(T newItemToLoad)
{
    // SORT SHORTEST TO TALLEST FIRST 
    if(numPeople == MAXSIZE)
    {
        cout << "DA BUS IS FULL!!! WALK INSTEAD :(" << endl;
        return;
    }

    int position = numPeople;

    for(int i = 0; i < numPeople; i++) 
    {
        if(!(items[i] < newItemToLoad)) 
        {
            position = i; // found person taller than new person
            break;
        }
    }

    // if new person !tallest --> shift current items by 1 to make space for new person
    for(int j = numPeople; j > position; j--) 
    {
        items[j] = items[j-1]; 
    }

    items[position] = newItemToLoad;
    numPeople++;
} 

template <class T>
void Bus<T>::moving() const
{
    cout << "We have reached the next stop!" << endl;
}

template <class T>
int Bus<T>::getNumItems() const 
{
    return numPeople;
}

template <class T>
float Bus<T>::getBusFare()
{
    //busFare = calculateTotalFare();
    return busFare;
}

template <class T>
void Bus<T>::setBusFare(float newBusFare)
{
    busFare = newBusFare;
}

template <class T>
float Bus<T>::calculateTotalFare()
{
    busFare *= numPeople;
    return busFare;
}