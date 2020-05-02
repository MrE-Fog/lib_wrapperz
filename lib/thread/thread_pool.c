#include "thread_pool.h"
#include <stdlib.h>
#include <string.h>

thread_pool_t* create_thread_pool(int total_threads)	{
	thread_pool_t *t_pool = (thread_pool_t *) malloc(sizeof(*t_pool));
	t_pool->total_threads = total_threads;
	t_pool->thread = (thread_t *) malloc(total_threads * sizeof(*(t_pool->thread)));
	
	// Clearing every bit
	memset((void *) t_pool->thread, 0, total_threads * sizeof(*(t_pool->thread)));
	for(int i=0; i<t_pool->total_threads; ++i)	(t_pool->thread[i]).is_free = 1;

	return t_pool;
}

void destroy_thread_pool(thread_pool_t *t_pool)	{
	if (t_pool)	{
		if (t_pool->thread)	{
			free(t_pool->thread);
			t_pool->thread = NULL;
		}
		free(t_pool);
		t_pool = NULL;
	}
}

static void* execute_func(void* fn_ptr_w_args)	{
	fn_ptr_w_arg *fna = (fn_ptr_w_arg *) fn_ptr_w_args;
	fna->thread->is_free = 0;
	void *ret_val = fna->fn(fna->arg);
	fna->thread->is_free = 1;
	return ret_val;
}

int t_pool_work_assign(thread_pool_t *t_pool, fn_ptr_w_arg *arg)	{
	for (int i=0; i<t_pool->total_threads; ++i)	{
		if ((t_pool->thread[i]).is_free)	{
			arg->thread = (t_pool->thread + i);
			if (pthread_create(&(t_pool->thread[i]).t_id, (const pthread_attr_t *) &(t_pool->thread[i]).t_attr, execute_func, (void *) arg) == 0)	{
				return 1;	// Success
			}
		}
	}
	return 0;
}