default: coinChange

coinChange.o: coinChange.h coinChange.cpp
	g++ -Wall -g -c coinChange.cpp

coinChange: coinChange.o main.cpp
	g++ -Wall -g -o coinChange coinChange.o main.cpp
	
clean:
	rm coinChange.o
	
cleanall: clean
	rm coinChange