#include "./philosophers.h"

int	stop_philo(t_tab *table)
{
	pthread_mutex_lock(&table->mutex_is_running);
	table->is_running = 0;
	pthread_mutex_unlock(&table->mutex_is_running);
	join_all_threads(table);
	return (1);
}

int	is_philo_running(t_tab *table)
{
	int	status;

	pthread_mutex_lock(&table->mutex_is_running);
	status = table->is_running;
	pthread_mutex_unlock(&table->mutex_is_running);
	return (status);
}

void	join_all_threads(t_tab *table)
{
	t_philo	*first;

	pthread_mutex_lock(&table->mutex_is_running);
	first = table->philo;
	pthread_mutex_unlock(&table->mutex_is_running);
	while (table->philo)
	{
		pthread_join(table->philo->ptid, NULL);
		table->philo = table->philo->next;
		if (table->philo == first)
			break ;
	}
	pthread_join(table->monitor, NULL);
	ft_lstclear(&table->philo);
	pthread_mutex_destroy(&table->mutex_is_running);
	pthread_mutex_destroy(&table->mutex_print);
}

void	lock_forks(t_philo *philo)
{
	if (!ft_is_even(philo->id))
	{
		pthread_mutex_lock(&philo->fork);
		print_action(philo, TOOKFORK);
		pthread_mutex_lock(&philo->next->fork);
		print_action(philo, TOOKFORK);
	}
	else
	{
		pthread_mutex_lock(&philo->next->fork);
		print_action(philo, TOOKFORK);
		pthread_mutex_lock(&philo->fork);
		print_action(philo, TOOKFORK);
	}
}

void	unlock_forks(t_philo *philo)
{
	if (!ft_is_even(philo->id))
	{
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
	}
	else
	{
		pthread_mutex_unlock(&philo->next->fork);
		pthread_mutex_unlock(&philo->fork);
	}
}
