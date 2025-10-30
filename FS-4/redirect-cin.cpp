#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <string>

void initialize(int argc, char** argv) {
	if(argc != 2) {
		std::cerr << "invalid arguments" << std::endl;
		exit(EXIT_FAILURE);
	}
	int fd = open(argv[1], O_RDONLY);
	if(fd == -1) {
		std::cerr << "error opening file" << std::endl;
		exit(EXIT_FAILURE);
	}
	int d = dup2(fd, STDIN_FILENO);  
	if(d == -1) {
		std::cerr << "error dup2" << std::endl;
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
}

int main(int argc, char** argv) {
	initialize(argc, argv);
	
	std::string input;
	std::cin >> input;

	std::string reversed(input.rbegin(), input.rend());

	std::cout << reversed;
	
	return 0;
}
