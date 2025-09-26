all: main
main: main.o ComplexNum.o sort.o
	g++ -o main main.o ComplexNum.o sort.o
main.o: main.cpp
	g++ -c main.cpp
ComplexNum.o: ComplexNum.cpp
	g++ -c ComplexNum.cpp
sort.o: sort.cpp
	g++ -c sort.cpp
clean:
	rm -f main *.o

