all: read-file
read-file: read-file.o
	g++ -o read-file read-file.o
read-file.o: read-file.cpp
	g++ -c read-file.cpp
clean:
	rm -f read-file *.o
