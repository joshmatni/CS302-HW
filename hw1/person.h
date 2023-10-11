#ifndef PERSON_H
#define PERSON_H

// This class defines a Person object with attributes for name and height
// Supports standard operations such as constructors, getters, setters, and a comparison operator based on height

#include <iostream>
using namespace std;

class Person
{
    string name;
    float height;

    public:
        Person();
        Person(string, float);
        Person(const Person&);

        string getName() const;
        float getHeight() const;

        void setName(const string);
        void setHeight(const float);
        
        bool operator<(const Person& person) const;

};
#endif