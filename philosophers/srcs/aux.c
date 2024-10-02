/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 00:23:27 by bruno             #+#    #+#             */
/*   Updated: 2024/10/02 02:43:09 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/philosophers.h"

int	get_current_time(t_philo *philo)
{
	int current_time;

	gettimeofday(&philo->info.time, 0);
	current_time = (philo->info.time.tv_sec * 1000) + (philo->info.time.tv_usec / 1000);
	return (current_time);
}

int	time_since_start(t_philo *philo)
{
	int	current_time = get_current_time(philo);
	return (current_time - philo->info.start_time);
}

int	time_since_last(t_philo *philo)
{
	int	current_time = get_current_time(philo);
	current_time = current_time - philo->info.last_meal;
	return (current_time);
}

void	lock(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	print_action(philo, TOOKFORK);

	pthread_mutex_lock(&philo->next->fork);
	print_action(philo, TOOKFORK);
}

void	unlock(t_philo *philo)
{
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
}

