// Authors: Ploy Wandeevong and Josh Matni (CS302 HW 4, Group 19)
// Purpose: Event Implementation
// Date: 10/13/2023

#include "event.h"

Event::Event()
{
    type = 'X';
    time = 0;
    length = 0;
}

Event::Event(char newType, int newTime, int newLength)
{
    type = newType;
    time = newTime;
    length = newLength;
}

char Event::getType() const
{
    return type;
}

void Event::setType(const char ty)
{
    type = ty;
}

int Event::getTime() const
{
    return time;
}

void Event::setTime(const int t)
{
    time = t;
}

int Event::getLength() const
{
    return length;
}
void Event::setLength(const int newLen)
{
    length = newLen;
}

bool Event::operator <(const Event& rhs) const
{
    //cout << "Comparing EVENT times: " << this->time << " > " << rhs.time << endl;
    return this->time < rhs.time;
}