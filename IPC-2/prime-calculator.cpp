#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <vector>
#include <sys/wait.h>

#define buffSize 100

bool checkPrime(int n) {
    if (n % 2 == 0 || n % 3 == 0) {
	    return false;
    }    
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
		return false;
	}	
    }
    return true;
}

void addPrimesToArr(int n, std::vector<int>& arr) {
    for (int i = arr.back() + 1; arr.size() < n; ++i) {
        if(checkPrime(i)) {
            arr.push_back(i);
        }
    }
}


int main() {
    int rwPipefd[2];
    int wrPipefd[2];
    int rwPipe = pipe(rwPipefd);
    int wrPipe = pipe(wrPipefd);
    if (rwPipe == -1 || wrPipe == -1) {
        std::cerr << "error: cannot create pipes" << std::endl;
        exit(EXIT_FAILURE);
    }

    pid_t child = fork();
    if(child == -1) {
        std::cerr << "error:failed create a child" << std::endl;
        exit(EXIT_FAILURE);
    }
    if(child == 0) {
        close(rwPipefd[0]);
        close(wrPipefd[1]);
        std::vector<int> arr = {2, 3, 5, 7};
        while(true) {
            char buff[buffSize];
            int readBytes = read(wrPipefd[0], buff, buffSize);
            if(readBytes == -1) {
                std::cerr << "error to read file" << std::endl;
                exit(EXIT_FAILURE);
            } if(readBytes) {
                buff[readBytes] = '\0';
                int n = std::atoi(buff);
                std::cout << "[Child] Calculating " << n << "-th prime number..." << std::endl;
                if(n > arr.size()) {
                    addPrimesToArr(n, arr);
                }

                std::cout << "[Child] Sending calculation result of prime(" << n << ")... " << std::endl;

                std::string res = std::to_string(arr[n - 1]);
                int writtenBytes = write(rwPipefd[1], res.c_str(), res.size());
                if(writtenBytes == -1) {
                    std::cerr << "error to write in file" << std::endl;
                    exit(EXIT_FAILURE);
                }
            } else {
                break;
            }
        }
        close(rwPipefd[1]);
        close(wrPipefd[0]);
    }
    else if(child > 0) {
        close(rwPipefd[1]);
        close(wrPipefd[0]);
        std::string m;
        while(true){
            char buff[buffSize] ;
            std::cout << "[Parent] Please enter the number: ";
            std::cin >> m;
            if(m == "exit") {
                close(wrPipefd[1]);
                close(rwPipefd[0]);
                wait(NULL);
                break;
            } else if(std::stoi(m) <= 0) {
                std::cout << "invalid number" << std::endl;
                continue;
            }
            std::cout << "[Parent] Sending " << m << " to the child process..." << std::endl;
            std::cout << "[Parent] Waiting for the response from the child process...\n";
            int writtenBytes = write(wrPipefd[1], m.c_str(), m.size());
            if(writtenBytes == -1) {
                std::cerr << "error to write in file" << std::endl;
                exit(EXIT_FAILURE);
            }
            int readBytes = read(rwPipefd[0], buff, buffSize);
            if(readBytes == -1) {
                std::cerr << "error to read file" << std::endl;
                exit(EXIT_FAILURE);
            } else if (readBytes) {
                buff[readBytes] = '\0';
                int res = std::atoi(buff);
                std::cout << "[Parent] Received calculation result of prime(" << m << ") = " << res << "...\n\n";
            }
        }
    }

    return 0;
}
