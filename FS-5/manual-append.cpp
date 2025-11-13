#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

int main(int argc, char** argv) {
	if(argc != 2) {
		std::cerr << "invalid arguments" << std::endl;
		exit(EXIT_FAILURE);
	}
	int fd1 = open(argv[1], O_WRONLY | O_RDONLY | O_TRUNC, 0644);
	if(fd1 == -1) {
		std::cerr << "error opening file" << std::endl;
		exit(EXIT_FAILURE);
	}
	int fd2 = dup(fd1);
	if(fd2 == -1) {
		std::cerr << "error duplicate file" << std::endl;
		close(fd1);
		exit(EXIT_FAILURE);
	}
	const char* fline = "first line\n";
	int write_fline = write(fd1, fline, strlen(fline));
	if(write_fline == -1) {
		std::cerr << "error write in first file" << std::endl;
                close(fd1);
		close(fd2);
                exit(EXIT_FAILURE);
	}
	const char* sline = "second line\n";
	int write_sline = write(fd2, sline, strlen(sline));
        if(write_sline == -1) {
                std::cerr << "error write in second file" << std::endl;
                close(fd1);
                close(fd2);
                exit(EXIT_FAILURE);
        }
	close(fd1);
	close(fd2);

	return 0;
}
