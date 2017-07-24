default: maxSub

maxSubarray.o: maxSubarray.h maxSubarray.cpp
	g++ -Wall -g -c maxSubarray.cpp

maxSub: maxSubarray.o main.cpp
	g++ -Wall -g -o maxSub maxSubarray.o main.cpp
	
clean:
	rm maxSubarray.o
	
cleanall: clean
	rm maxSub