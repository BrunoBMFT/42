/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:25:32 by bruno             #+#    #+#             */
/*   Updated: 2024/11/27 17:38:51 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

bool	is_sim_running(t_table *table)
{
	bool	status;

	pthread_mutex_lock(&table->is_running_mutex);
	status = table->is_running;
	pthread_mutex_unlock(&table->is_running_mutex);
	return (status);
}

void	join_threads(t_table *table)
{
	t_philo	*first;

	pthread_mutex_lock(&table->is_running_mutex);
	first = table->philo;
	pthread_mutex_unlock(&table->is_running_mutex);
	while (table->philo)
	{
		pthread_join(table->philo->ptid, NULL);
		table->philo = table->philo->next;
		if (table->philo == first)
			break ;
	}
	pthread_join(table->observer, NULL);
	ft_lstclear(&table->philo);
	pthread_mutex_destroy(&table->is_running_mutex);
	pthread_mutex_destroy(&table->print_mutex);
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
