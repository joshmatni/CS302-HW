#ifndef BUS_H
#define BUS_H

#include "transporter.h"

// Defines a templated Bus class inherited from the Transporter base class, specialized for handling people transportation
// Includes functionalities for fare management, passenger sorting, and basic transporter operations

template <class T>
class Bus: public Transporter<T>
{
    float busFare; 
    int numPeople;
    T items[MAXSIZE];

    public:
        Bus();
        Bus(T*, int, float);
        Bus(const Bus&);

        // From transporter
        void unloadItemFromTransporter() override;
        void emptyAllItems() override;
        bool isEmpty() const override;
        void loadItemToTransporter(T) override; 
        void moving() const override;
        int getNumItems() const override;

        // self methods
        T* getItems();
        float getBusFare();
        void setBusFare(float);
        float calculateTotalFare();
};
#include "bus.cpp"
#endif