#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <thread>
#include <vector>

void part_sum(const std::vector<int>& arr, unsigned long start,
                 unsigned long end, long long res) {
	long long sum = 0;
	for(int i = start; i < end; ++i) {
		sum += arr[i];
	}
	res = sum;
}

int main(int argc, char** argv) {
	if(argc != 3) {
		std::cerr << "error: invalid arguments" << std::endl;
		exit(EXIT_FAILURE);
	}
	unsigned long N = std::stoul(argv[1]);
	unsigned int M = std::stoul(argv[2]); 
	if(N < 1000000) {
		std::cerr << "error: invalid argument for array" << std::endl;
		exit(EXIT_FAILURE);
	}
	if(M == 0) {
		std::cerr << "error: invalid arguments" << std::endl;
                exit(EXIT_FAILURE);
	}
	
	std::vector<int> arr(N);
	for(int i = 0; i < 100000; ++i) {
		arr[i] = rand(); 
	}
	
	clock_t start_seq = clock();
    	long long sum_seq = 0;
    	for (unsigned long i = 0; i < N; ++i) {
        	sum_seq += arr[i];
    	}
    	clock_t end_seq = clock();
    	double dur_seq = double(end_seq - start_seq) / CLOCKS_PER_SEC;
	
	clock_t start_th = clock();
	long long sum_th = 0;
        std::vector<std::thread> th;
    	std::vector<long long> res(M, 0);
	unsigned long part = N/M;
        for (unsigned long i = 0; i < M; ++i) {
                unsigned long st = i * part;
		unsigned long end = (i == M - 1) ? N : st + part;
		th.emplace_back(part_sum, std::ref(arr), st, end, std::ref(res[i]));
        }
	for(auto& x : th) {
		x.join();
	}
	for(long long x : res) {
		sum_th += x;
	}
        clock_t end_th = clock();
	double dur_th = double(end_th - start_th) / CLOCKS_PER_SEC;

	std::cout << "Time spent without threads: " << dur_seq << std::endl;
    std::cout << "Time spent with " << M << " threads: " << dur_th << std::endl;

	return 0;
}
