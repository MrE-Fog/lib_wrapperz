#ifndef _CHATAPP_THREAD_POOL_H_
#define _CHATAPP_THREAD_POOL_H_

#include <pthread.h>

typedef struct thread_t	{
	pthread_t t_id;
	pthread_attr_t t_attr;
	int is_free;
} thread_t;

typedef struct thread_pool_t	{
	int total_threads;
	thread_t *thread;
} thread_pool_t;

typedef struct fn_ptr_w_arg	{
	void* (*fn)(void*);
	thread_t *thread;
	void* arg;
} fn_ptr_w_arg;

thread_pool_t* create_thread_pool(int total_threads);
void destroy_thread_pool(thread_pool_t *t_pool);
int t_pool_work_assign(thread_pool_t *t_pool, fn_ptr_w_arg *arg);

#endif
