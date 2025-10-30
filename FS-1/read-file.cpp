#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	int size = 4096;
	char buffer[size];
	if(argc != 2) {
		std::cerr << "invalid argument" << std::endl;
		exit(EXIT_FAILURE); 
	}
	int fd = open(argv[1], O_RDONLY);
	if(fd == -1) {
		std::cerr << "error opening file" << std::endl;
		exit(EXIT_FAILURE);	
	}
	ssize_t bytes_read = read(fd, buffer, size);
	if(bytes_read == -1) {
		std::cerr << "error reading file" << std::endl;
		close(fd);
		exit(EXIT_FAILURE);	
	}
	while(bytes_read > 0) {
		ssize_t written_bytes = write(1, buffer, bytes_read);
		if(written_bytes == -1) {
		std::cerr << "error trying to write in file" << std::endl;
		close(fd);
		exit(EXIT_FAILURE);	
	}
		bytes_read = read(fd, buffer, size);
		if(bytes_read == -1) {
		std::cerr << "error reading file" << std::endl;
		close(fd);
		exit(EXIT_FAILURE);	
	}
	}
	if(bytes_read == -1) {
                std::cerr << "error reading file" << std::endl;
				close(fd);
                exit(EXIT_FAILURE);
	}
	close(fd);

	return 0;
}
