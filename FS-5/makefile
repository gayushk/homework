all: manual-append
manual-append: manual-append.o
	g++ -o manual-append manual-append.o
manual-append.o: manual-append.cpp
	g++ -c manual-append.cpp
clean:
	rm -f manual-append *.o
