#include "./philosophers.h"

int	ft_usleep(t_philo *philo, int time)
{
	int	start;

	start = get_time();
	while (get_time() - start < time)
	{
		if (died_while_waiting(philo) && is_philo_running(philo->table))
			return (0);
		usleep(10);
	}
	return (1);
}

int	eat_action(t_philo *philo)
{
	lock_forks(philo);
	print_action(philo, EATING);
	pthread_mutex_lock(&philo->mutex_last_meal);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->mutex_last_meal);
	pthread_mutex_lock(&philo->info.mutex_num_times_eat);
	philo->info.num_times_eat--;
	if (philo->info.num_times_eat == 0)
		philo->done_eating = 1;
	pthread_mutex_unlock(&philo->info.mutex_num_times_eat);
	if (!ft_usleep(philo, philo->info.eat_time))
		return (0);
	unlock_forks(philo);
	return (1);
}

int	sleep_action(t_philo *philo)
{
	print_action(philo, SLEEPING);
	if (!ft_usleep(philo, philo->info.sleep_time))
		return (0);
	return (1);
}

int	think_action(t_philo *philo)
{
	print_action(philo, THINKING);
	if (!ft_usleep(philo, philo->info.think_time))
		return (0);
	return (1);
}

void	*philo_loop(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->info.num_times_eat != 0)
	{
		if (!is_philo_running(philo->table))
			break ;
		if (!eat_action(philo))
			break ;
		if (!sleep_action(philo))
			break ;
		if (!think_action(philo))
			break ;
	}
	return (NULL);
}
