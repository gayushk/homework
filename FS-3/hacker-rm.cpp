#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char** argv) {
	if(argc != 2) {
		std::cerr << "invalid arguments" << std::endl;
		exit(EXIT_FAILURE);
	}
	const char* path = argv[1];
	struct stat st;
	if(stat(path, &st) == -1) {
		std::cerr << "we don't have that path" << std::endl;
		exit(EXIT_FAILURE);
	}
	off_t f_size = st.st_size;
	int fd = open(path, O_RDWR);
	if(fd == -1) {
		std::cerr << "error opening file" << std::endl;
		exit(EXIT_FAILURE);
	}
	if(f_size == 0) {
		close(fd);
		unlink(path);
		exit(EXIT_SUCCESS);
       	}
	size_t size = 4096;
	char buf_zeros[size];
	off_t count = f_size;
	off_t s = lseek(fd, 0, SEEK_SET);
	if(s == -1) {
		std::cerr << "error lseek" << std::endl;
		close(fd);
		exit(EXIT_FAILURE);
	}
	while(count != 0) {
		if(size > f_size) {
			size = f_size;
		}
		int b_write = write(fd, buf_zeros, size);
		f_size -= b_write; 	
	}
	close(fd);
	unlink(path);

	return 0;
}
