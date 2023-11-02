# makefile

all: clean server client

common.o: common.h common.cpp
	g++ -g -w -std=c++11 -c common.cpp

Histogram.o: Histogram.h Histogram.cpp
	g++ -g -w -std=c++11 -c Histogram.cpp

TCPreqchannel.o: TCPreqchannel.h TCPreqchannel.cpp
	g++ -g -w -std=c++11 -c TCPreqchannel.cpp

client: client.cpp Histogram.o TCPreqchannel.o common.o
	g++ -g -w -std=c++11 -o client client.cpp Histogram.o TCPreqchannel.o common.o -lpthread -lrt -fsanitize=address -fno-omit-frame-pointer

server: server.cpp  TCPreqchannel.o common.o
	g++ -g -w -std=c++11 -o server server.cpp TCPreqchannel.o common.o -lpthread -lrt -fsanitize=address -fno-omit-frame-pointer



clean:
	rm -rf *.o fifo* server client 
