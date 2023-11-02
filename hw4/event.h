// Authors: Ploy Wandeevong and Josh Matni (CS302 HW 4, Group 19)
// Purpose: Declaration for Event Class
// Date: 10/13/2023

#ifndef EVENT_H
#define EVENT_H

class Event
{
    char type;
    int time, length;

    public:
        Event();
        Event(char, int, int);

        bool operator <(const Event& rhs) const;
        
        char getType() const;
        void setType(const char);

        int getTime() const;
        void setTime(const int);

        int getLength() const;
        void setLength(const int);
};
#endif