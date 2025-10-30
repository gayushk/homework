#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	int size = 4096;
	char buffer[size];
	if(argc != 3) {
		std::cerr << "invalid argument" << std::endl;
		exit(EXIT_FAILURE); 
	}
	int fd1 = open(argv[1], O_RDONLY);
	if(fd1 == -1) {
		std::cerr << "error opening file" << std::endl;
		exit(EXIT_FAILURE);	
	}
	int fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(fd2 == -1) {
                std::cerr << "error opening file" << std::endl;
                close(fd1);
                exit(EXIT_FAILURE);
        }
	ssize_t bytes_read = read(fd1, buffer, size);
	while(bytes_read > 0) {
		ssize_t bytes_written = write(fd2, buffer, bytes_read);
		if(bytes_written == -1) {
                	std::cerr << "error trying to write in file" << std::endl;
                	close(fd1);
			close(fd2);
                	exit(EXIT_FAILURE);
        	}
        }
	if(bytes_read == -1) {
		std::cerr << "error reading file" << std::endl;
		close(fd1);
		close(fd2);
		exit(EXIT_FAILURE);	
	}
	close(fd1);
	close(fd2);

	return 0;
}
