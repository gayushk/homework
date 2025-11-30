#include "parallel_scheduler.h"
#include <iostream>
#include <unistd.h>

void printTask(void* arg){
	int id = *static_cast<int*>(arg);
	std::cout << "started: " << id << std::endl;
	usleep(1000);
       	std::cout << "finished: " << id << std::endl;	
}

int main() {
	parallel_scheduler p(3);
	int arr[10];
	for(int i = 0; i < 10; ++i) {
		arr[i] = i;
		p.run(printTask, &arr[i]);	
	}
	return 0;
}
