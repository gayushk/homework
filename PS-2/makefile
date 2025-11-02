all: interactive-shell
interactive-shell: interactive-shell.o
	g++ -o interactive-shell interactive-shell.o
interactive-shell.o: interactive-shell.cpp
	g++ -c interactive-shell.cpp
clean: 
	rm -f interactive-shell *.o
