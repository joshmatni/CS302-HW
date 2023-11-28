trees: driver.o
	g++ -o trees driver.o

driver.o: driver.cpp LinkedBTree.h linkedtreenode.h LinkedBSearchTree.h
	g++ -std=c++11 -c driver.cpp

clean:
	rm *.o trees