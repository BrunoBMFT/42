
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    pthread_mutex_t *lock;
    int thread_id;
}	t_philo;

void* trythis(void* arg)
{
	t_philo *philo = (t_philo*)arg;

	printf("%d is trying to acquire the lock\n", philo->thread_id);
	pthread_mutex_lock(philo->lock);

	sleep(1);

	printf("%d has acquired the lock and started working\n", philo->thread_id);

	sleep(1);

	pthread_mutex_unlock(philo->lock);
	printf("%d has released the lock\n", philo->thread_id);

	return NULL;
}

int main(void)
{
	pthread_t 		tid[2];
	pthread_mutex_t lock;
	t_philo 		philo[2];

	pthread_mutex_init(&lock, NULL);
	for (int i = 0; i < 2; i++) 
	{
		philo[i].lock = &lock;//what is locked is the entire philo it seems
		philo[i].thread_id = i + 1;
		pthread_create(&tid[i], NULL, &trythis, &philo[i]);
	}

	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);

	pthread_mutex_destroy(&lock);

	return 0;
}


/* pthread_t tid[2];
int counter;
pthread_mutex_t lock;

void* trythis(void* arg)
{
    pthread_mutex_lock(&lock);

    unsigned long i = 0;
    counter += 1;
    printf("\n Job %d has started\n", counter);

    for (i = 0; i < (0xFFFFFFFF); i++)
        ;
    printf("\n Job %d has finished\n", counter);
    pthread_mutex_unlock(&lock);

    return NULL;
}

int main(void)
{
    int i = 0;
  
    pthread_mutex_init(&lock, NULL);
    while (i < 2) 
	{
        pthread_create(&(tid[i]), NULL, &trythis, NULL);
        i++;
    }

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_mutex_destroy(&lock);

    return 0;
} */
