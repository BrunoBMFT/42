/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:25:32 by bruno             #+#    #+#             */
/*   Updated: 2024/11/06 19:08:53 by bruno            ###   ########.fr       */
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
	bool	status;

	status = get_bool(&philo->table->status_mutex, philo->table->status);
	return (status);
}

void	stop_sim(t_philo *philo)
{
	set_bool(&philo->table->status_mutex, &philo->table->status, false);
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
	// if (!ft_is_even(philo->id))
	// {
	// 	pthread_mutex_unlock(&philo->fork);
	// 	pthread_mutex_unlock(&philo->next->fork);
	// }
	// else
	// {
	// 	pthread_mutex_unlock(&philo->next->fork);
	// 	pthread_mutex_unlock(&philo->fork);
	// }
}

void	lock_forks(t_philo *philo)
{
	
	pthread_mutex_lock(&philo->fork);
	print_action(philo, TOOKFORK);
	pthread_mutex_lock(&philo->next->fork);
	print_action(philo, TOOKFORK);
	// if (!ft_is_even(philo->id))//for some reason, it makes philos eat when they shouldnt
	// {
	// 	pthread_mutex_lock(&philo->fork);
	// 	print_action(philo, TOOKFORK);
	// 	pthread_mutex_lock(&philo->next->fork);
	// 	print_action(philo, TOOKFORK);
	// }
	// else if (!ft_is_even(philo->id))
	// {
	// 	pthread_mutex_lock(&philo->next->fork);
	// 	print_action(philo, TOOKFORK);
	// 	pthread_mutex_lock(&philo->fork);
	// 	print_action(philo, TOOKFORK);
	// }
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
	ft_lstclear(&table->philo);
	pthread_mutex_destroy(&table->status_mutex);
}
