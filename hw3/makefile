postfix: driver.o 
	g++ driver.o -o postfix

driver.o: driver.cpp linkedStack.h arrayStack.h node.h
	g++ -std=c++11 -c driver.cpp

clean:
	rm *.o postfix