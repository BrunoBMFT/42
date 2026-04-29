#include "./philosophers.h"

int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, 0);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print_action(t_philo *philo, int action)
{
	int	time;

	pthread_mutex_lock(&philo->table->mutex_print);
	time = get_time() - philo->table->start_time;
	if (action == DIED)
		printf("%d %d died\n", time, philo->id);
	if (!is_philo_running(philo->table))
		return (pthread_mutex_unlock(&philo->table->mutex_print), (void) NULL);
	if (action == TOOKFORK)
		printf("%d %d has taken a fork\n", time, philo->id);
	if (action == EATING)
		printf("%d %d is eating\n", time, philo->id);
	if (action == SLEEPING)
		printf("%d %d is sleeping\n", time, philo->id);
	if (action == THINKING)
		printf("%d %d is thinking\n", time, philo->id);
	pthread_mutex_unlock(&philo->table->mutex_print);
}
