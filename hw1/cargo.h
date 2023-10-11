#ifndef CARGO_H
#define CARGO_H

// Definition of the Cargo class representing different types of cargo with their respective weights
// Supports cargo merging using operator overloading and standard getters and setters

#include <string>
using namespace std;

class Cargo
{
    string type;
    float weight;

    public:
        Cargo();
        Cargo(string, float);
        Cargo(const Cargo&);

        string getType() const;
        float getWeight() const;

        void setType(const string);
        void setWeight(const float);
        
        Cargo& operator+=(const Cargo&);
};
#endif