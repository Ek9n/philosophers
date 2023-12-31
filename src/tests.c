#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //Header file for sleep(). man 3 sleep for details.
#include <pthread.h>

// A normal C function that is executed as a thread
// when its name is specified in pthread_create()
void *philosopher(void *vargp)
{
	(void) *vargp;
	sleep(1);
	printf("Printing GeeksQuiz from Thread \n");
	return NULL;
}

int main()
{
	pthread_t t1;
	pthread_t t2;
	printf("Before Thread\n");
	pthread_create(&t1, NULL, philosopher, NULL);
	pthread_join(t1, NULL);
	// pthread_join(t2, NULL);
	printf("After Thread\n");
	pthread_create(&t2, NULL, philosopher, NULL);
	pthread_join(t2, NULL);
	exit(0);
}
