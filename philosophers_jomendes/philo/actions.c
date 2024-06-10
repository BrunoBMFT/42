/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:35:32 by jomendes          #+#    #+#             */
/*   Updated: 2024/06/10 11:15:17 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo)
{
	unsigned long	current_time;

	current_time = get_time(philo->info->start_time);
	pthread_mutex_lock(&philo->info->lock);
	if (current_time > philo->time_to_die)
	{
		if (philo->info->dead == 0)
		{
			philo->info->dead = 1;
			pthread_mutex_lock(&philo->info->message);
			printf("%lu %d died\n", current_time, philo->id);
			pthread_mutex_unlock(&philo->info->message);
		}
		pthread_mutex_unlock(&philo->info->lock);
		return (1);
	}
	if (philo->info->dead == 1)
	{
		pthread_mutex_unlock(&philo->info->lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->lock);
	return (0);
}

int	start_eating(t_philo *philo)
{
	unsigned long	start_time;
	unsigned long	eating_time;

	if (is_dead(philo))
		return (1);
	start_time = get_time(philo->info->start_time);
	eating_time = philo->info->time_to_eat;
	pthread_mutex_lock(&philo->info->message);
	if (philo->info->dead == 0)
		printf("%lu %d is eating\n", \
		get_time(philo->info->start_time), philo->id);
	pthread_mutex_unlock(&philo->info->message);
	while ((get_time (philo->info->start_time) - start_time) < eating_time)
	{
		if (is_dead(philo))
			return (1);
		usleep(1);
	}
	pthread_mutex_lock(&philo->meal_mutex);
	philo->meals_counter++;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (is_dead(philo))
		return (1);
	return (0);
}

int	start_sleeping(t_philo *philo)
{
	unsigned long	start_time;
	unsigned long	sleeping_time;

	if (is_dead(philo))
		return (1);
	start_time = get_time(philo->info->start_time);
	sleeping_time = philo->info->time_to_sleep;
	pthread_mutex_lock(&philo->info->message);
	if (philo->info->dead == 0)
		printf("%lu %d is sleeping\n", \
		get_time(philo->info->start_time), philo->id);
	pthread_mutex_unlock(&philo->info->message);
	while ((get_time(philo->info->start_time) - start_time) < sleeping_time)
	{
		if (is_dead(philo))
			return (1);
		usleep(1);
	}
	if (is_dead(philo))
		return (1);
	return (0);
}

void	start_thinking(t_philo *philo)
{
	usleep(20);
	pthread_mutex_lock(&philo->info->message);
	if (philo->info->dead == 0)
		printf("%lu %d is thinking\n", \
		get_time(philo->info->start_time), philo->id);
	pthread_mutex_unlock(&philo->info->message);
}
