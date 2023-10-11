#ifndef TRANSPORTER_H
#define TRANSPORTER_H

#include <iostream>
using namespace std;
#define MAXSIZE 50

// The Transporter template class defines common transportation behaviors and 
// serves as a pure virtual interface for concrete transport classes 
// for Bus and Train. It has a maximum size set to 50 items

template <class T>
class Transporter
{
    public:
        virtual void unloadItemFromTransporter() = 0;
        virtual void emptyAllItems() = 0;
        virtual bool isEmpty() const = 0;
        virtual void loadItemToTransporter(T) = 0; 
        virtual void moving() const = 0;
        virtual int getNumItems() const = 0; // report how many
};
#endif
