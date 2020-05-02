#include "lib/thread/thread_pool.h"
#include <stdio.h>
#include <locale.h>
#include <unistd.h>
#include <wchar.h>

void do_this(void *arg)	{
	for (int i=0; i<10; ++i)	{
		printf("[%d] %lc\n", __LINE__, 0x1F378);
		sleep(1);
	}
}

void do_that(void *arg)	{
	for (int i=0; i<10; ++i)	{
		printf("[%d] %lc\n", __LINE__, 0x1F379);
		sleep(1);
	}
}

void print_this(void *arg)	{
	for (int i=0; i<5; ++i)	{
		printf("[%d] %lc!\n", __LINE__, 0x1F380);
		sleep(1);
	}
}

int main()	{
	setlocale(LC_ALL, "en_US.utf8");
	thread_pool_t *t_pool = create_thread_pool(2);

	fn_ptr_w_arg first, second, third;

	first.fn = &do_this;
	second.fn = &do_that;
	third.fn = &print_this;

	first.arg = second.arg = third.arg = NULL;
	first.thread = second.thread = third.thread = NULL;

	if (t_pool_work_assign(t_pool, &first))	{
		printf("[I] Thread 1\n");
	}
	if (t_pool_work_assign(t_pool, &second))	{
		printf("[I] Thread 2.\n");
	}
	if (t_pool_work_assign(t_pool, &third))	{
		printf("[I] Thread 3\n");
	}

	for(int i=0; i<t_pool->total_threads; ++i)	{
		pthread_join(t_pool->thread[i].t_id, NULL);
	}

	destroy_thread_pool(t_pool);
}