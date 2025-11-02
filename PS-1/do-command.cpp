#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>

void do_command(char** argv) {
	struct timeval start, end;
	gettimeofday(&start, nullptr);
	pid_t pid = fork();
	if(pid < 0) {
		std::cerr << "error fork" << std::endl;
		exit(1);
	} else if(pid == 0) {
		execvp(argv[0], argv);
		std::cerr << "error execvp" << std::endl;
		exit(127);
	} else {
		int status;
		if(waitpid(pid, &status, 0) == -1) {
			std::cerr << "error waitpid" << std::endl;
			exit(1);
		}
		gettimeofday(&end, nullptr);
		double t = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0
		int exit_c = 0;
		if(WIFEXITED(status)) {
			exit_c = WEXITSTATUS(status);
		} else {
			exit_c = -1;
		}
		std::cout << "Command completed with " << exit_c << "exit code and took" << t << "seconds." << std::endl;
	}
}

int main(int argc, char** argv) {
	if(argc < 2){
		std::cerr << "invalid arguments" << std::endl;
		exit(EXIT_FAILURE);
	}
	do_command(&argv[1]);
	return 0;	
}	
