/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:25:32 by bruno             #+#    #+#             */
/*   Updated: 2024/11/07 21:30:26 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	get_int(pthread_mutex_t *mutex, int from)
{
	int	value;

	pthread_mutex_lock(mutex);
	value = from;
	pthread_mutex_unlock(mutex);
	return (value);
}

void	set_int(pthread_mutex_t *mutex, int *to_set, int value)
{
	pthread_mutex_lock(mutex);
	(*to_set) = value;
	pthread_mutex_unlock(mutex);
}

int	get_bool(pthread_mutex_t *mutex, bool from)
{
	bool	value;

	pthread_mutex_lock(mutex);
	value = from;
	pthread_mutex_unlock(mutex);
	return (value);
}

void	set_bool(pthread_mutex_t *mutex, bool *to_set, bool value)
{
	pthread_mutex_lock(mutex);
	(*to_set) = value;
	pthread_mutex_unlock(mutex);
}

bool		is_sim_running(t_philo *philo)
{
	bool	is_running;

	is_running = get_bool(&philo->table->is_running_mutex, philo->table->is_running);
	return (is_running);
}

bool	is_dead(t_philo *philo)
{
	int	time_since_last;

	time_since_last = get_time() - philo->last_meal;//get_int for mutex safety
	if (time_since_last < philo->info.time_die)
		return (false);//still alive
	stop_sim(philo);
	return (true);
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

void	stop_sim(t_philo *philo)
{
	set_bool(&philo->table->is_running_mutex, &philo->table->is_running, false);
}

int	get_time(void)
{
	struct timeval time;

	gettimeofday(&time, 0);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	join_threads(t_table *table)
{
	t_philo *first = table->philo;
	while (table->philo)
	{
		pthread_mutex_destroy(&table->philo->fork);
		pthread_mutex_destroy(&table->philo->last_meal_mutex);
		pthread_join(table->philo->ptid, NULL);
		table->philo = table->philo->next;
		if (table->philo == first)//doesnt break, for some reason
			break ;
	}
	pthread_join(table->observer, NULL);
	ft_lstclear(&table->philo);
	pthread_mutex_destroy(&table->is_running_mutex);
}
