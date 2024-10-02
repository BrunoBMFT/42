#include "includes/philosophers.h"

typedef struct s_philo
{
	int	count;
}				t_philo;

void	*compute(void *philovoid)
{
	t_philo *philo = (t_philo *) philovoid;
	printf("called philo: %d\n", philo->count);
	pthread_exit(NULL);
}

int	main(int ac, char **av)
{
	if (!av[1])
		return 0;

	t_philo philo;
	printf("here\n");
	philo.count = ft_atoi(av[1]);
	pthread_t thread;

	pthread_create(&thread, NULL, compute, (void *) &philo);
	pthread_join(thread, NULL);
	return 0;
}
