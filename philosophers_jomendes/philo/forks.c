/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:48:41 by jomendes          #+#    #+#             */
/*   Updated: 2024/06/07 13:28:36 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	try_eat_even(t_philo *philo)
{
	pthread_mutex_lock(&philo->r_fork->mutex);
	if (!philo->r_fork->available)
	{
		pthread_mutex_unlock(&philo->r_fork->mutex);
		return (0);
	}
	pthread_mutex_lock(&philo->l_fork->mutex);
	if (!philo->l_fork->available)
	{
		pthread_mutex_unlock(&philo->r_fork->mutex);
		pthread_mutex_unlock(&philo->l_fork->mutex);
		return (0);
	}
	return (1);
}

int	try_eat_odd(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork->mutex);
	if (!philo->l_fork->available)
	{
		pthread_mutex_unlock(&philo->l_fork->mutex);
		return (0);
	}
	pthread_mutex_lock(&philo->r_fork->mutex);
	if (!philo->r_fork->available)
	{
		pthread_mutex_unlock(&philo->l_fork->mutex);
		pthread_mutex_unlock(&philo->r_fork->mutex);
		return (0);
	}
	return (1);
}

int	are_forks_available(t_philo *philo)
{
	if (philo->id % 2 == 0)
		return (try_eat_even(philo));
	else
		return (try_eat_odd(philo));
}

void	grab_forks(t_philo *philo)
{
	philo->r_fork->available = 0;
	if (!is_dead(philo))
	{
		pthread_mutex_lock(&philo->info->message);
		if (philo->info->dead == 0)
			printf("%lu %d has taken a fork\n", \
			get_time(philo->info->start_time), philo->id);
		pthread_mutex_unlock(&philo->info->message);
	}
	pthread_mutex_unlock(&philo->r_fork->mutex); 
	philo->l_fork->available = 0;
	if (!is_dead(philo))
	{
		pthread_mutex_lock(&philo->info->message);
		if (philo->info->dead == 0)
			printf("%lu %d has taken a fork\n", \
			get_time(philo->info->start_time), philo->id);
		pthread_mutex_unlock(&philo->info->message);
	}
	pthread_mutex_unlock(&philo->l_fork->mutex);
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork->mutex);
	philo->l_fork->available = 1;
	pthread_mutex_unlock(&philo->l_fork->mutex);
	pthread_mutex_lock(&philo->r_fork->mutex);
	philo->r_fork->available = 1;
	pthread_mutex_unlock(&philo->r_fork->mutex);
}
