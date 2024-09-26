#include <stdio.h>
#include <pthread.h>

void	*compute(void *numpoint)
{
	int sum = 0;
	int *num = (int *) numpoint;

	for (long i = 0; i < 1000000000; i++)
		sum += *num;

	printf("Compute: %d\n", *num);
	return (NULL);
	//pthread_exit(NULL);
}

int	main(int ac, char **av)
{
	pthread_t thread1;
	pthread_t thread2;

	int value1 = 1;
	int value2 = 5;
/* 	compute( (void*) &value1);
	compute( (void*) &value2); */

	pthread_create(&thread1, NULL, compute, (void *) &value1);
	pthread_join(thread1, NULL);


	pthread_create(&thread2, NULL, compute, (void *) &value2);
	pthread_join(thread2, NULL);

	return 0;
}