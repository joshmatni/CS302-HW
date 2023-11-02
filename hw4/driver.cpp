// Authors: Ploy Wandeevong and Josh Matni (CS302 HW 4, Group 19)
// Purpose: Implementing an array based queue and problems from text book
// Date: 10/13/2023

#include "arrayQueue.h"
#include "priorityQueue.h"
#include "customer.h"
#include "event.h"
#include <fstream>
#define INPUTFILE "input.txt"

void processArrival(Event&, PriorityQueue<Event>&, ArrayQueue<Customer>&, int& currentTime, bool&);
void processDeparture(Event&, PriorityQueue<Event>&, ArrayQueue<Customer>&, int& currentTime, bool&);

int main()
{
    ArrayQueue<Customer> bankQueue;
    PriorityQueue<Event> eventListQueue; // line of customers in bank
    int total_waitingTime, currentTime, departureTime;
    int numCustomers = 0;
    double totalWait, totalArrival, totalProcess = 0;

    //create customers and load info from file into each one
    ifstream input(INPUTFILE);
    if(input.is_open())
    {
        while(input.good())
        {
            int time, len;
            input >> time >> len;

            Event newArrivalEvent = Event('a', time, len);
            eventListQueue.enqueue(newArrivalEvent);
        }
    input.close();
    }
    else
    {
        cout << "Could not open file" << endl;
        return 1;
    }

    bool tellerAvailable = true;

    while(!eventListQueue.isEmpty())
    {
        Event newEvent = eventListQueue.peekFront();
        eventListQueue.dequeue();
        currentTime = newEvent.getTime();

        if(newEvent.getType() == 'a') // event is arrival event
        {
            cout << "Processing Arrival Event, Current Time: " << currentTime << endl;
            processArrival(newEvent, eventListQueue, bankQueue, currentTime, tellerAvailable);
            numCustomers++;

            totalArrival += currentTime;
            totalProcess += newEvent.getLength();
        }
        
        else if(newEvent.getType() == 'd')
        {
            cout << "Processing Departure Event, Current Time: " << currentTime << endl;
            processDeparture(newEvent, eventListQueue, bankQueue, currentTime, tellerAvailable);
            totalWait += currentTime;
        }
        //cout << "EVENTS LIST QUEUE: " << eventListQueue.peekFront().getTime() << '\n';
    }

    totalWait = (totalWait - totalArrival - totalProcess) / numCustomers;
    cout <<  endl << "Number of Customers Served: " << numCustomers << endl;
    cout << "Average Wait Time: " << totalWait << " minutes" << endl;
    return 0;
}

void processArrival(Event& customer_event, PriorityQueue<Event>& eventQueue, ArrayQueue<Customer>& bankQueue, int& currentTime, bool& tellerAvailable)
{
    if(bankQueue.isEmpty() && tellerAvailable) // creates departure event
    {

        int departureTime = currentTime + customer_event.getLength();
        Event newDepartureEvent = Event('d', departureTime, 0); // no length
        eventQueue.enqueue(newDepartureEvent);
        tellerAvailable = false;

    }
    else
    {
        Customer newCustomer = Customer(customer_event.getTime(), customer_event.getLength());
        bankQueue.enqueue(newCustomer);
    }
}

void processDeparture(Event& customer_event, PriorityQueue<Event>& eventQueue, ArrayQueue<Customer>& bankQueue, int& currentTime, bool& tellerAvailable)
{
    if(!bankQueue.isEmpty())
    {

        Customer newCustomer = Customer(bankQueue.peekFront().getTimeArrived(), bankQueue.peekFront().getLen());
        bankQueue.dequeue();
        int departureTime = currentTime + newCustomer.getLen();
        Event newDepartureEvent = Event('d', departureTime, 0);
        eventQueue.enqueue(newDepartureEvent);
    }
    else
    {
        tellerAvailable = true;       
    }
}

//TODO: WEE WOO WWEEE WOOO WWEE WOOO