// Authors: Ploy Wandeevong and Josh Matni (CS302 HW 4, Group 19)
// Purpose: Customer Declarations
// Date: 10/13/2023

#ifndef CUSTOMER_H
#define CUSTOMER_H

class Customer
{
    int timeArrived, transaction_len;
    
    public:
        Customer();
        Customer(int, int);
        Customer(const Customer&);
        bool operator >(const Customer& rhs) const;

        int getTimeArrived() const;
        void setTimeArrived(const int);

        int getLen() const;
        void setLen(const int);
};
#endif