all: demo-application
parallel_scheduler.so: parallel_scheduler.cpp
	g++ -fpic -shared -pthread parallel_scheduler.cpp -o $@
demo-application: demo.cpp parallel_scheduler.so
	g++ -pthread demo.cpp parallel_scheduler.so -o demo-application -Wl,-rpath=.
clean:
	rm -f *.so demo-application
