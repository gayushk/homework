#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>

void execute_command(char** argv, bool silent = false){
	pid_t pid = fork();
	if(pid < 0) {
		std::cerr << "error fork" << std::endl;
		exit(EXIT_FAILURE);
	} else if(pid == 0) {
		if(silent) {
			char fname[32];
			snprintf(fname, sizeof(fname), "%d.log", getpid());
			int lfd = open(fname, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if(lfd == -1) {
				std::cerr << "error opening file" << std::endl;
				exit(EXIT_FAILURE);
			} else {
				dup2(lfd, STDOUT_FILENO);
				dup2(lfd, STDERR_FILENO);
				close(lfd);
			}
		}
	        char cwd[1024];
		if(getcwd(cwd, sizeof(cwd)) != nullptr) {
			std::string path = std::string(cwd) + ":";
			char* old = getenv("PATH");
			if(old) {
				path += old;
			} else {
				path += "/bin:/usr/bin";
			}
			setenv("PATH", path.c_str(), 1);
		}	
		execvp(argv[0], argv);
		std::cerr << "error command" << std::endl;
		exit(EXIT_FAILURE);
	} else {
		int status;
		wait(&status);
		int exit_c = 0;
		if(WIFEXITED(status)) {
			exit_c = WEXITSTATUS(status);
			if(exit_c != 0) {
				std::cout << exit_c << std::endl;
			}
		}	
	}
}

int main(int argc, char** argv) {
	std::string line;
    	char* args[64] = {nullptr};
    	bool silent = false;
    	while (std::cout << "shell> ", std::getline(std::cin, line)) {
        	if (line.empty()) continue;
        	size_t pos = 0;
        	int i = 0;
        	pos = line.find_first_not_of(" \t");
        	if (pos == std::string::npos) continue;
        	line = line.substr(pos);
        	if (line.substr(0, 6) == "silent") {
            		silent = true;
            		pos = line.find_first_not_of(" \t", 6);
            		if (pos == std::string::npos) continue;
            		line = line.substr(pos);
        	} else {
            		silent = false;
        	}
        	pos = line.find_first_of(" \t");
        	std::string first = (pos == std::string::npos) ? line : line.substr(0, pos);
        	if (first == "exit") break;
        	while (!line.empty() && i < 63) {
            		pos = line.find_first_of(" \t");
            		std::string word = (pos == std::string::npos) ? line : line.substr(0, pos);
            		args[i++] = const_cast<char*>(word.c_str());
			if (pos == std::string::npos) break;
            		pos = line.find_first_not_of(" \t", pos);
            		if (pos == std::string::npos) break;
            		line = line.substr(pos);
        	}
        	args[i] = nullptr;

        	execute_command(args, silent);
    	}
	return 0;	
}	

