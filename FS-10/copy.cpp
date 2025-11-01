#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

int main(int argc, char** argv) {
	if(argc != 3) {
		std::cerr << "invalid arguments" << std::endl;
		exit(EXIT_FAILURE);
	}
	char* path1 = argv[1];
	char* path2 = argv[2];
	struct stat st;
	if((stat(path1, &st)) == -1) {
		std::cerr << "file does not exist" << std::endl;
		exit(EXIT_FAILURE);
	}
	off_t log_size = st.st_size;
	if(log_size < 3) {
                std::cerr << "error, invalid file size" << std::endl;
                exit(EXIT_FAILURE);
        }
	int fd1 = open(path1, O_RDONLY);
	if(fd1 == -1) {
		std::cerr << "error opening file" << std::endl;
		exit(EXIT_FAILURE);
	}
	int fd2 = open(path2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if(fd2 == -1) {
                std::cerr << "error opening file" << std::endl;
		close(fd1);
                exit(EXIT_FAILURE);
        }
	size_t buf_size = 4096;
	char buffer[buf_size];
	off_t data = 0;
	off_t holes = 0;
	off_t pos = 0;
	while(log_size != 0) {
		ssize_t bytes_read = read(fd1, buffer, buf_size);
		if(bytes_read == -1) {
			std::cerr << "" << std::endl;
			close(fd1);
			close(fd2);
			exit(EXIT_FAILURE);
		}
		if(bytes_read == 0) {
			break;
		}
		bool is_hole = true;
		for(ssize_t i = 0; i < bytes_read; ++i) {
			if(buffer[i] != '\0') {
				is_hole = false;
				break;
			}
		}
		if(is_hole) {
			if(lseek(fd2, bytes_read, SEEK_CUR) == -1) {
				std::cerr << "error lseek" << std::endl;
				close(fd1);
				close(fd2);
				exit(EXIT_FAILURE);
			}
			holes += bytes_read;
		} else {
			ssize_t written_bytes = write(fd2, buffer, bytes_read);
			if(written_bytes != bytes_read) {
				std::cerr << "error lseek" << std::endl;
                                close(fd1);
                                close(fd2);
                                exit(EXIT_FAILURE);
			}
			data += bytes_read;
		}
		pos += bytes_read;
		
	}
	close(fd1);
	close(fd2);

	return 0;
}

