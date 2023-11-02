all: clean run-tdll run

run-tdll: TDLList-main.o 
	c++ -std=c++11 TDLList-main.o -o run-tdll

TDLList-main.o: TDLList-main.cpp TemplatedDLList.h
	c++ -std=c++11 -c TDLList-main.cpp

clean:
	rm -f *.o run-tdll

run:
	./run-tdll
