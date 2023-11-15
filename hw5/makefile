sorting: driver.o
	g++ -o sorting driver.o

driver.o: driver.cpp metrics.h
	g++ -std=c++11 -c driver.cpp

clean:
	rm *.o sorting