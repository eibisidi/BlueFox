#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define SIZE (128)

#define SIMPLE_LOCK_INITIALIZER {0}
#define TICKET_LOCK_INITIALIZER {0}

extern void simple_lock(void *l);
extern void simple_unlock(void *l);
extern void ticket_lock(void *l);
extern void ticket_unlock(void *l);

typedef struct {
	long owner;
}simple_lock_t;

typedef struct {
	long next_current;
}ticket_lock_t;

static struct {
	long counter[SIZE];
	pthread_mutex_t mutex;
	simple_lock_t simple_lock;
	ticket_lock_t ticket_lock;
}shared_resource = {
	.mutex = PTHREAD_MUTEX_INITIALIZER,
	.simple_lock = SIMPLE_LOCK_INITIALIZER,
	.ticket_lock = TICKET_LOCK_INITIALIZER,
};

static int data_raced;

#ifdef LOCK_NONE
#define LOCK()
#define UNLOCK()
#define LOCK_TYPE "LOCK_NONE"
#endif

#ifdef LOCK_PTHREAD
#define LOCK() pthread_mutex_lock(&(shared_resource.mutex))
#define UNLOCK() pthread_mutex_unlock(&(shared_resource.mutex))
#define LOCK_TYPE "LOCK_PTHREAD"
#endif

#ifdef LOCK_SIMPLE
#define LOCK() simple_lock(&(shared_resource.simple_lock))
#define UNLOCK() simple_unlock(&(shared_resource.simple_lock))
#define LOCK_TYPE "LOCK_SIMPLE"
#endif

#ifdef LOCK_TICKET
#define LOCK() ticket_lock(&(shared_resource.ticket_lock))
#define UNLOCK() ticket_unlock(&(shared_resource.ticket_lock))
#define LOCK_TYPE "LOCK_TICKET"
#endif

void * read_proc(void *)
{
	int i;

	while (1) {
		LOCK();
		if (shared_resource.counter[0] != shared_resource.counter[SIZE-1])
			break;
		UNLOCK();
	}

	printf("data race detected!\n");
	data_raced = 1;
}

void * write_proc(void *)
{
	int i;

	while (!data_raced) {
		LOCK();
		for (i = 0; i < SIZE; ++i) {
			++shared_resource.counter[i];
			asm volatile("dmb sy");
		}
		UNLOCK();
	}
}

int main(int argc, char *argv[])
{
	pthread_t reader, writer;
	int ret;

	printf(LOCK_TYPE "\n");
	ret = pthread_create(&reader, NULL, read_proc, NULL);
	if (ret) {
		printf("reader create failed with %d\n", ret);
		exit(-1);
	}

	ret = pthread_create(&writer, NULL, write_proc, NULL);
	if (ret) {
		printf("writer create failed with %d\n", ret);
		exit(-1);
	}

	pthread_join(reader, NULL);
	pthread_join(writer, NULL);

	return 0;
}

