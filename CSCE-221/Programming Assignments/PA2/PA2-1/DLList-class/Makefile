all: clean run-dll run

run-dll: DLList.o DLList-main.o
	c++ -g -std=c++11 DLList.o DLList-main.o -o run-dll

DLList.o: DLList.cpp DLList.h
	c++ -g -std=c++11 -c DLList.cpp

DLList-main.o: DLList-main.cpp DLList.h
	c++ -g -std=c++11 -c DLList-main.cpp

clean:
	rm -f *.o run-dll

run:
	./run-dll

