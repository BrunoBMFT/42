#include "./philosophers.h"

int	died_while_waiting(t_philo *philo)
{
	int	time_since_last;

	pthread_mutex_lock(&philo->mutex_last_meal);
	time_since_last = get_time() - philo->last_meal;
	pthread_mutex_unlock(&philo->mutex_last_meal);
	if (time_since_last > philo->info.die_time)
	{
		pthread_mutex_lock(&philo->table->mutex_is_running);
		philo->table->is_running = 0;
		pthread_mutex_unlock(&philo->table->mutex_is_running);
		return (1);
	}
	return (0);
}

void	increment_done_eating(t_tab *table, t_philo	*current)
{
	pthread_mutex_lock(&current->table->mutex_print);
	table->all_done++;
	pthread_mutex_unlock(&current->table->mutex_print);
}

int	monitor_check(t_tab *table)
{
	t_philo	*current;
	t_philo	*first;

	pthread_mutex_lock(&table->mutex_print);
	current = table->philo;
	first = table->philo;
	pthread_mutex_unlock(&table->mutex_print);
	while (current)
	{
		if (died_while_waiting(current))
			return (print_action(current, DIED), 0);
		pthread_mutex_lock(&current->info.mutex_num_times_eat);
		if (current->done_eating)
			increment_done_eating(table, current);
		pthread_mutex_unlock(&current->info.mutex_num_times_eat);
		if (table->all_done == table->philo_num)
			return (0);
		current = current->next;
		if (current == first)
			break ;
	}
	return (1);
}

void	*monitor_experiment(void *tab)
{
	t_tab	*table;

	table = (t_tab *)tab;
	while (is_philo_running(table))
	{
		if (!monitor_check(table))
			break ;
		usleep(50);
	}
	return (NULL);
}

void	single(t_philo *philo)
{
	printf("0 1 has taken a fork\n");
	usleep(philo->info.die_time * 1000);
	printf("%d 1 died\n", philo->info.die_time);
	ft_lstclear(&philo);
	exit (0);
}
