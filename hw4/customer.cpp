// Authors: Ploy Wandeevong and Josh Matni (CS302 HW 4, Group 19)
// Purpose: Customer Implementation
// Date: 10/13/2023

#include "customer.h"
Customer::Customer()
{
    timeArrived = 0;
    transaction_len = 0;
}

Customer::Customer(int newTimeArrived, int newTransaction_len)
{
    timeArrived = newTimeArrived;
    transaction_len = newTransaction_len;
}

Customer::Customer(const Customer& rhs)
{
    timeArrived = rhs.timeArrived;
    transaction_len = rhs.transaction_len;
}

bool Customer::operator >(const Customer& rhs) const
{
    //cout << "Comparing TIME ARRIVED times: " << this->timeArrived << " > " << rhs.timeArrived << endl;
    return this->timeArrived > rhs.timeArrived;
}

int Customer::getTimeArrived() const
{
    return timeArrived;
}
void Customer::setTimeArrived(const int time)
{
    timeArrived = time;
}

int Customer::getLen() const
{
    return transaction_len;
}

void Customer::setLen(const int len)
{
    transaction_len = len;
}