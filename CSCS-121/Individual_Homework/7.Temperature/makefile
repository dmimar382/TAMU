all: TemperatureQueriesOne github

clean:
	rm main.o TemperatureQueriesOne

TemperatureQueriesOne: main.o
	g++ -std=c++17 -Wall -Wextra -pedantic -fsanitize=address,undefined -g -o TemperatureQueriesOne main.o

main.o:
	g++ -std=c++17 -Wall -Wextra -pedantic -fsanitize=address,undefined -c -g *.cpp
	
SHELL := /bin/bash
	
github:
	cd /csce && ./github.sh;