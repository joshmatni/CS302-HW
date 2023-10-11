transport: driver.o cargo.o person.o
	g++ -o transport driver.o cargo.o person.o

driver.o: driver.cpp person.h cargo.h bus.h train.h
	g++ -std=c++11 -c driver.cpp

person.o: person.h person.cpp
	g++ -std=c++11 -c person.cpp

cargo.o: cargo.h cargo.cpp
	g++ -std=c++11 -c cargo.cpp

clean:
	rm *.o transport