all: hacker-rm
hacker-rm: hacker-rm.o
	g++ -o hacker-rm hacker-rm.o
hacker-rm.o: hacker-rm.cpp
	g++ -c hacker-rm.cpp
clean:
	rm -f hacker-rm *.o
