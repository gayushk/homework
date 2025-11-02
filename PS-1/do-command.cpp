#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

void do_command(char** argv) {
	int argc = 0;
	while(argv[argc] != nullptr) {
	       ++argc;
	}
	pid_t pid = fork();
	if(pid < 0) {
		std::cerr << "error fork" << std::endl;
		exit(EXIT_FAILURE);
	} else if(pid == 0) {
		execvp(argv[0], argv);
		std::cerr << "error command" << std::endl;
		exit(EXIT_FAILURE);
	} else {
		int status;
		wait(&status);
		int exit_c = 0;
		if(WIFEXITED(status)) {
			exit_c = WEXITSTATUS(status);
		} else if(WIFSIGNALED(status)) {
			exit_c = 128 + WTERMSIG(status);
		}	
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
