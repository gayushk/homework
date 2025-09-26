#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char** argv) {
	int size = 4096;
	char buffer[size];
	if(argc != 3) {
		perror("invalid arguments");
		exit(EXIT_FAILURE);
	}
	int fd1 = open(argv[1], O_RDONLY);
	if(fd1 == -1) {
		perror("error opening file1");
		exit(EXIT_FAILURE);
	}
	int fd2 = open(argv[2], O_WRONLY | O_CREAT, 0664);
	if(fd2 == -1) {
                perror("error opening file2");
                exit(EXIT_FAILURE);
        }
	ssize_t bytes_read = read(fd1, buffer, size);
	while(bytes_read > 0) {
		ssize_t written_bytes = write(fd2, buffer, bytes_read);
		bytes_read = read(fd1, buffer, size);
	}
	if(bytes_read == -1) {
		perror("error reading file");
                exit(EXIT_FAILURE);
	}
	close(fd1);
	close(fd2);

	return 0;
}
