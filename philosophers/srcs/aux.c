/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:25:32 by bruno             #+#    #+#             */
/*   Updated: 2024/10/17 21:42:47 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

bool		is_sim_running(t_philo *philo)
{
	bool	status;

	pthread_mutex_lock(&philo->table->status_mutex);
	status = philo->table->status;
	pthread_mutex_unlock(&philo->table->status_mutex);
	return (status);
}

void	stop_sim(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->status_mutex);
	philo->table->status = false;
	pthread_mutex_unlock(&philo->table->status_mutex);
}

void	unlock_forks(t_philo *philo)
{
/* 	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork); */
	
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

void	lock_forks(t_philo *philo)//have the has_died func running in loop
{
	
	if (!ft_is_even(philo->id))
	{
		pthread_mutex_lock(&philo->fork);
		print_action(philo, TOOKFORK);
		pthread_mutex_lock(&philo->next->fork);
		print_action(philo, TOOKFORK);
	}
	else if (!ft_is_even(philo->id))
	{
		pthread_mutex_lock(&philo->next->fork);
		print_action(philo, TOOKFORK);
		pthread_mutex_lock(&philo->fork);
		print_action(philo, TOOKFORK);
	}
/* 	pthread_mutex_lock(&philo->fork);
	print_action(philo, TOOKFORK);
	pthread_mutex_lock(&philo->next->fork);
	print_action(philo, TOOKFORK); */
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
		{
			printf("here\n");
			break ;
		}
	}
	ft_lstclear(&table->philo);
	pthread_mutex_destroy(&table->status_mutex);
}
