#include "parallel_scheduler.h"
#include <iostream>

parallel_scheduler::parallel_scheduler(size_t capacity) {
	pthread_mutex_init (&mutex_, nullptr);
	pthread_cond_init (&cond_, nullptr);
	threads.resize(capacity);
	for(size_t i = 0; i < capacity; ++i) {
		pthread_create(&threads[i], nullptr, thr_tramp, this);
	}
}

parallel_scheduler::~parallel_scheduler() {
	 pthread_mutex_lock(&mutex_);
	 stop_ = true;
	 pthread_mutex_unlock(&mutex_);
	 pthread_cond_broadcast(&cond_);
	 for(pthread_t t : threads) {
	 	pthread_join(t, nullptr);
	 }
	pthread_mutex_destroy(&mutex_);
	pthread_cond_destroy(&cond_);
}

void* parallel_scheduler::thr_tramp(void* arg) {
	static_cast<parallel_scheduler*>(arg)->worker_thr();
	return nullptr;
}

void parallel_scheduler::worker_thr() {
	while(true){
		Task task{};
        	pthread_mutex_lock(&mutex_);
		while(!stop_ && q.empty()) {
			pthread_cond_wait(&cond_, &mutex_);
		}
		if(stop_ && q.empty()) {
			pthread_mutex_unlock(&mutex_);
			return;
		}
		task = q.front();
		q.pop();
		pthread_mutex_unlock(&mutex_);
		task.func(task.arg);
	}
}

void parallel_scheduler::run(void(*func)(void*), void* arg) {
	pthread_mutex_lock(&mutex_);
	q.push(Task{func, arg});
	pthread_mutex_unlock(&mutex_);
	pthread_cond_signal(&cond_);
}
