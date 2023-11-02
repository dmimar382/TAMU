all: clean test run

test: Stress_ball.o  Jeans.o  Collection_test.o 
	c++ -std=c++11 Stress_ball.o Jeans.o Collection_test.o -o test

Stress_ball.o: Stress_ball.cpp Stress_ball.h
	c++ -std=c++11 -c Stress_ball.cpp

Jeans.o: Jeans.cpp Jeans.h
	c++ -std=c++11 -c Jeans.cpp

# Stress_ball_test.o: Stress_ball_test.cpp Stress_ball.h
# 	c++ -std=c++11 -c Stress_ball_test.cpp

# Jeans_test.o: Jeans_test.cpp Jeans.h
# 	c++ -std=c++11 -c Jeans_test.cpp

Collection_test.o:  Stress_ball.h Jeans.h Collection.h Collection_test.cpp 
		c++ -std=c++11 -c Collection_test.cpp 


clean:
	rm -f *.o test

run:
	./test
