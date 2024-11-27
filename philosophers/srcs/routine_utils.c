/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:25:32 by bruno             #+#    #+#             */
/*   Updated: 2024/11/26 22:11:21 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	stop_sim(t_table *table)
{
	set_bool(&table->is_running_mutex, &table->is_running, false);
	join_threads(table);
	return (1);
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

void	join_threads(t_table *table)
{
	t_philo	*first;

	first = table->philo;
	while (table->philo)
	{
		pthread_mutex_destroy(&table->philo->fork);
		pthread_mutex_destroy(&table->philo->last_meal_mutex);
		pthread_join(table->philo->ptid, NULL);
		table->philo = table->philo->next;
		if (table->philo == first)
			break ;
	}
	pthread_join(table->observer, NULL);
	ft_lstclear(&table->philo);
	pthread_mutex_destroy(&table->is_running_mutex);
}
