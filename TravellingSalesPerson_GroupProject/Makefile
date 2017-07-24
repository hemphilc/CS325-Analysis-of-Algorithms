default: tsp

coinChange.o: tsp.h tsp.cpp
	g++ -Wall -g -c tsp.cpp

tsp: tsp.o main.cpp
	g++ -Wall -g -o tsp tsp.o main.cpp
	
clean:
	rm tsp.o
	
cleanall: clean
	rm tsp