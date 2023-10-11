#ifndef TRAIN_H
#define TRAIN_H 

#include "transporter.h"

// Defines a templated Train class that inherits from the Transporter base class.
// Provides specialized functionalities specific to handling cargos and their weight.

template <class T>
class Train: public Transporter<T>
{
    float total_weight;
    T items[MAXSIZE];
    int numCargo;

    public:
        Train();
        Train(T*, int, float);
        Train(const Train&);

        float getTotalWeight() const;
        void setTotalWeight(const float); 

        // From transporter
        T* getItems();
        void unloadItemFromTransporter() override;
        void emptyAllItems()  override;
        bool isEmpty() const override;
        void loadItemToTransporter(T) override; 
        void moving() const override; 
        int getNumItems() const override;
};
#include "train.cpp"
#endif

