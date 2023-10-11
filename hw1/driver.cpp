// Joshua Matni
// CS 302 PA 1
// 9/06/2023
// Main application showcasing functionalities of Bus and Train transporters with Person and Cargo objects
// Provides detailed tests for loading, moving, unloading, and other related operations on both transporters

#include "bus.h"
#include "person.h"
#include "cargo.h"
#include "train.h"

int main()
{
    //! For Train
    Cargo *cargos;
    Cargo cargo1("hay", 2.3);
    Cargo cargo2("coal", 5);
    Cargo cargo3("coal", 8.62);
    Train<Cargo> train(cargos, 0, 0);

    // Load cargos onto the train
    train.loadItemToTransporter(cargo1);
    train.loadItemToTransporter(cargo2);
    train.loadItemToTransporter(cargo3);

    // Check if train is empty
    cout << "Is the train empty?" << endl;
    if(train.isEmpty()) 
    {
        cout << "The Train is not carrying any cargo!" << endl << endl;
    } 
    else 
    {
        cout << "Nope! There are: " << train.getNumItems() << " cargos on the train!" << endl << endl;
    }

    // Display total weight of cargos
    cout << "TOTAL WEIGHT OF CARGOS: " << train.getTotalWeight() << endl << endl;

    // Display individual cargos
    cout << "Let's check the cargos on the train:" << endl;
    for(int i = 0; i < train.getNumItems(); i++)
    {
        cout << "Cargo " << i << " Type: " << train.getItems()[i].getType() << ", Weight: " << train.getItems()[i].getWeight() << endl;
    }

    cout << endl << "Train is moving!" << endl;
    train.moving();
    cout << endl;

    // Unloading cargo
    cout << "Unloading a cargo. Goodbye!" << endl;
    train.unloadItemFromTransporter();
    cout << "How many cargos are left?" << endl;
    for(int i = 0; i < train.getNumItems(); i++)
    {
        cout << "Cargo " << i << " Type: " << train.getItems()[i].getType() 
            << ", Weight: " << train.getItems()[i].getWeight() << endl;
    }

    // Empty all cargos
    cout << endl << "Unloading ALL cargos from the train!" << endl;
    train.emptyAllItems();
    cout << "Cargos on train now?: " << train.getNumItems() << endl;
    cout << "\n\n\n\n";

    //! For Bus
    cout << "BUS PORTION!!!!" << endl << endl;

    Person *people;
    Person person1("Taylor", 5.2);
    Person person2("Lana", 3);
    Person person3("Charlie", 10.3);
    Bus<Person> bus(people, 0, 1.5);
    
    bus.loadItemToTransporter(person1);
    bus.loadItemToTransporter(person2);
    bus.loadItemToTransporter(person3);
    
    cout << "Is the bus empty?" << endl;
    if(bus.isEmpty() == true)
    {
        cout << "The Bus has no one in it!" << endl << endl;
    }
    else if(bus.isEmpty() == false)
    {
        cout << "Nope! There are: " << bus.getNumItems() << " on the bus!" << endl << endl;
    }

    // calculate fare 
    cout << "The BUS FARE is: $" << bus.calculateTotalFare() << endl << endl;

   
    // Check for ordering heights
    cout << "Lets check if everyone is sitting shortest to tallest!" << endl;
    for(int i = 0; i < bus.getNumItems(); i++)
    {
        cout << "Person " << i << " Height: " << bus.getItems()[i].getHeight() << ", Name: " << bus.getItems()[i].getName() << endl;
    }

    cout << endl << "Bus moving!" << endl;
    bus.moving();
    cout << endl;

    // test for unload
    cout << "Someone needs to get off! BYEEEEE!!!" << endl;
    bus.unloadItemFromTransporter();
    cout << "Okay peeps how many of yall are left??" << endl;
    for(int i = 0; i < bus.getNumItems(); i++)
    {
        cout << "Person " << i << " Height: " << bus.getItems()[i].getHeight() << ", Name: " << bus.getItems()[i].getName() << endl;
    }

    // test for empty 
    cout << endl << "EVERYONE GETTTT OUTTT OF THE BUS!" << endl;
    bus.emptyAllItems();
    cout << "People on bus now?: " << bus.getNumItems() << endl;

    return 0;
}