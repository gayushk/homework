all: redirect-cin
redirect-cin: redirect-cin.o
	g++ -o redirect-cin redirect-cin.o
redirect-cin.o: redirect-cin.cpp
	g++ -c redirect-cin.cpp
clean:
	rm -f redirect-cin *.o
