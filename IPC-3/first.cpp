#include "shared.h"
#include <iostream>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string>

int main() {
    shared_array array("array", 10);

    sem_t* sem = sem_open("/array_sem", O_CREAT, 0666, 1);

    while (true) {
        sem_wait(sem);
        for (size_t i = 0; i < 10; ++i) {
            ++array[i];
        }
     	
	std::cout << "First inc at array[0] " << array[0] << std::endl;

        sem_post(sem);
        sleep(2);
    }

    sem_unlink("/array_sem");
    sem_close(sem);

    return 0;
}
