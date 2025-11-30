#ifndef parallel_scheduler_h
#define parallel_scheduler_h

#include <pthread.h>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <mutex>
#include <functional>

struct Task{
	void(*func)(void*);
	void* arg;
};

class parallel_scheduler{
	size_t capacity;

	static void* thr_tramp(void* arg);
	void worker_thr();

	std::vector<pthread_t> threads;
	std::queue<Task> q;
	pthread_mutex_t mutex_;
	pthread_cond_t cond_;
	bool stop_ = false;
	public:
		explicit parallel_scheduler(size_t capacity);
	       ~parallel_scheduler();
       		void run(void(*func)(void*), void* arg);		
};

#endif
