/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:46:50 by jomendes          #+#    #+#             */
/*   Updated: 2024/06/10 11:30:04 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	special_case(t_philo *philo)
{
	if (philo->info->n_philos == 1)
	{
		pthread_mutex_lock(&philo->info->message);
		printf("%lu %d is thinking\n", \
		get_time(philo->info->start_time), philo->id);
		pthread_mutex_unlock(&philo->info->message);
		usleep(philo->info->time_to_die * 1000);
		pthread_mutex_lock(&philo->info->message);
		printf("%lu %d is dead\n", \
		get_time(philo->info->start_time), philo->id);
		pthread_mutex_unlock(&philo->info->message);
		return (1);
	}
	return (0);
}

int	exec_routine(t_philo *philo)
{
	while (!are_forks_available(philo))
	{
		if (is_dead(philo))
			return (1);
	}
	grab_forks(philo);
	pthread_mutex_lock(&philo->info->lock);
	philo->time_to_die = get_time(philo->info->start_time) \
	+ philo->info->time_to_die;
	pthread_mutex_unlock(&philo->info->lock);
	if (start_eating(philo))
		return (1);
	release_forks(philo);
	if (start_sleeping(philo))
		return (1);
	return (0);
}

void	*routine(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	philo->time_to_die = get_time(philo->info->start_time) + \
	philo->info->time_to_die;
	if (special_case(philo))
		return ((void *)0);
	while (1)
	{
		if (is_dead(philo))
			break ;
		if (exec_routine(philo))
			break ;
		if (philo->meals_counter == philo->info->n_meals)
			break ;
		if (is_dead(philo))
			break ;
		start_thinking(philo);
	}
	return ((void *)0);
}

int	main(int ac, char **av)
{
	t_info	info;

	if (ac < 5 || ac > 6)
	{
		write (2, "Wrong augments\n", 15);
		return (1);
	}
	if (init_program(av, &info) != 0)
	{
		info.philos = NULL;
		info.forks = NULL;
		free(info.philos);
		free(info.forks);
		return (1);
	}
	run_program(&info);
	finish_program(&info);
	return (0);
}
