#include <pthread.h>
#include <stdio.h>
//error codes of pthread_create and pthread_join
void *helloWorld(void *arg)
{
	(void)(arg);
	printf("in pthread\n");
	return (void *)0;
}

int	main(void) 
{
	pthread_t myThread;
	int exitCode = 0;

	printf("before pthread_create\n");
	pthread_create(&myThread, NULL, &helloWorld, NULL);
	printf("after pthread_create\n");
	pthread_join(myThread, NULL);
	printf("after pthread_join\n");

	return 0;
}