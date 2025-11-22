all: array-summary
array-summary: array-summary.o
	g++ -o array-summary array-summary.o
array-summary.o: array-summary.cpp
	g++ -c array-summary.cpp
clean: 
	rm -f array-summary *.o

