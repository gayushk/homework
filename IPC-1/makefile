all: signal-echo
signal-echo: signal-echo.o
	g++ -o signal-echo signal-echo.o
signal-echo.o: signal-echo.cpp
	g++ -c signal-echo.cpp
clean:
	rm -f signal-echo *.o
