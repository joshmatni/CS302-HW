#include "person.h"

// Defines a Person class with attributes name and height, supporting comparison based on height
// Provides methods for retrieving and modifying the name and height, and compares two Person objects based on height

Person::Person()
{
    name = "NONE";
    height = 1;
}

Person::Person(string newName, float newHeight)
{
    name = newName;
    height = newHeight;
}

Person::Person(const Person &rhs)
{
    name = rhs.name;
    height = rhs.height;
}

string Person::getName() const
{
    return name;
}

float Person::getHeight() const
{
    return height;
}

void Person::setName(const string newName)
{
    name = newName;
}

void Person::setHeight(const float newHeight)
{
    height = newHeight;
}

// return true if the current object's height is less than the other object's height, and false otherwise
bool Person::operator<(const Person& somebody) const 
{
    return this->height < somebody.height;
}