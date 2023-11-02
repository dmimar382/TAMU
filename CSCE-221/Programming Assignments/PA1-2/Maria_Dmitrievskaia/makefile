all: clean test run

test: Stress_ball.o Stress_ball_test.o Collection.o 
	c++ -std=c++11 Stress_ball.o Stress_ball_test.o Collection.o collection_test.cpp -o test

Stress_ball.o: Stress_ball.cpp Stress_ball.h
	c++ -std=c++11 -c Stress_ball.cpp

Collection.o: Collection.cpp Collection.h 
	c++ -std=c++11 -c Collection.cpp 

Stress_ball_test.o: Stress_ball_test.cpp
	c++ -std=c++11 -c Stress_ball_test.cpp

collection_test.o: collection_test.cpp Stress_ball.h Stress_ball_test.cpp Collection.cpp Collection.h 
		c++ -std=c++11 -c collection_test.cpp -o test


clean:
	rm -f *.o test

run:
	./test
