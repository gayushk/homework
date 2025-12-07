#include <iostream>
#include <ctime>
#include <random>
#include <pthread.h>

class ThreadClass {
public:
    pthread_t tid;
    int* arr;
    int start;
    int end;
    int res;
};

void* ths_sum(void* arg){
    ThreadClass* tc = (ThreadClass*) arg;
    tc->res = 0;
    for(int i = tc->start; i < tc->end; i++) {
        tc->res += tc->arr[i];
    }
    return NULL;
}

void sum(int n, int count) {
    int arr[n];
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1, 10); 
    for (int i = 0; i < n; i++) { 
	    arr[i] = dis(gen); 
    }

    ThreadClass th_datas[count];
    int chunk = n / count;

    std::clock_t clock_start = std::clock();

    for (int i = 0; i < count; ++i) {
        th_datas[i].arr = arr;
        th_datas[i].start = i*chunk;
        th_datas[i].end = (i == count - 1) ? n : (i + 1) * chunk;
        int threadCreated = pthread_create(&th_datas[i].tid, NULL, ths_sum, (void*) &th_datas[i]); 
        if(threadCreated != 0){
            std::cerr << "error:cannot create new thread" << std::endl;
        }
    }
    long int th_sum = 0;
    for (int i = 0; i < count; ++i) {
        pthread_join(th_datas[i].tid, NULL);
        th_sum += th_datas[i].res;
    }
    std::clock_t clock_end = std::clock();
    double duration = 1000.0 * (clock_end - clock_start) / CLOCKS_PER_SEC;
    std::cout << "sum with threads took " << duration << " ms" << std::endl;
    std::cout << th_sum <<  "\n";

    clock_start = std::clock();
    long int sum = 0; 
    for (int i = 0; i < n; i++) { 
        sum += arr[i];
    }
    clock_end = std::clock();
    duration = 1000.0 * (clock_end - clock_start) / CLOCKS_PER_SEC;

    std::cout << "sum without threads took " << duration << " ms" << std::endl;
    std::cout << sum << std::endl;
}

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "error: invalid arguments" << std::endl;
        exit(EXIT_FAILURE);
    }

    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    sum(n, m);
    return 0;
}
