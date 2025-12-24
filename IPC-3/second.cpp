#include "shared.h"
#include <iostream>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <stdexcept>

int main() {
    shared_array array("array", 10);

    sem_t* sem = sem_open("/array_sem", O_CREAT, 0666, 1);
    while (true) {
        sem_wait(sem);
        std::cout << "Second: array values: ";
        for (size_t i = 0; i < 10; ++i) {
            std::cout << array[i] << " ";
        }
        std::cout << std::endl;
        sem_post(sem);
        sleep(3);
    }

    sem_close(sem);
    sem_unlink("/array_sem");

    return 0;
}
