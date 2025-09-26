#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	int size = 4096;
	char buffer[size];
	if(argc != 2) {
		perror("invalid argument");
		exit(EXIT_FAILURE); 
	}
	int fd = open(argv[1], O_RDONLY);
	if(fd == -1) {
		perror("error opening file");
		exit(EXIT_FAILURE);	
	}
	ssize_t bytes_read = read(fd, buffer, size);
	while(bytes_read > 0) {
		ssize_t written_bytes = write(1, buffer, bytes_read);
		bytes_read = read(fd, buffer, size);
	}
	if(bytes_read == -1) {
                perror("error reading file");
                exit(EXIT_FAILURE);
	}
	close(fd);

	return 0;
}
