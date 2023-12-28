tsp: driver.o
	g++ -o tsp driver.o

driver.o: driver.cpp arrayGraph.h
	g++ -std=c++11 -c driver.cpp

clean:
	rm *.o tsp