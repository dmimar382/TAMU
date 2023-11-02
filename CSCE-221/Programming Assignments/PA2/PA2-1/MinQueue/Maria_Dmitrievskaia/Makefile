all: clean test run

test: Minqueue.o 
	c++ -std=c++11 Minqueue.o -o test

Minqueue.o: Minqueue.cpp Minqueue.h
	c++ -std=c++11 -c Minqueue.cpp

clean:
	rm -f *.o test

run:
	./test
