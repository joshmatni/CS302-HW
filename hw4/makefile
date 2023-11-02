bank_sim: driver.o customer.o event.o
	g++ driver.o customer.o event.o -o bank_sim

driver.o: driver.cpp arrayQueue.h priorityQueue.h customer.h event.h
	g++ -std=c++11 -c driver.cpp 

event.o: event.cpp event.h
	g++ -std=c++11 -c event.cpp

customer.o: customer.cpp customer.h
	g++ -std=c++11 -c customer.cpp

clean:
	rm *.o bank_sim