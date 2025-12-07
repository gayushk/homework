all: prime-calculator
prime-calculator: prime-calculator.o
	g++ -o prime-calculator prime-calculator.o
prime-calculator.o: prime-calculator.cpp
	g++ -c prime-calculator.cpp
clean: 
	rm -f prime-calculator *.o
