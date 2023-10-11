#include "cargo.h"
// Implementation of the Cargo class, representing individual cargo items with type and weight properties
// Provides functionality for property access, modification, and cargo weight addition using operator overloading

Cargo::Cargo()
{
    type = "hay";
    weight = 1;
}

Cargo::Cargo(string newType, float newWeight)
{
    type = newType;
    weight = newWeight;
}

Cargo::Cargo(const Cargo &rhs)
{
    type = rhs.type;
    weight = rhs.weight;
}

string Cargo::getType() const
{
    return type;
}

float Cargo::getWeight() const
{
    return weight;
}

void Cargo::setType(const string newType)
{
    type = newType;
}

void Cargo::setWeight(const float newWeight)
{
    weight = newWeight;
}

Cargo& Cargo::operator+=(const Cargo& newCargo) 
{
    this->weight += newCargo.weight;  
    return *this; // return entire Cargo object
}
