/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:29:17 by jomendes          #+#    #+#             */
/*   Updated: 2024/05/31 12:29:31 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_forks(t_info *info)
{
	int	i;

	i = -1;
	info->start_time = get_time(0);
	while (++i < info->n_philos)
	{
		pthread_mutex_init(&info->forks[i].mutex, NULL);
		info->forks[i].available = 1;
		pthread_mutex_init(&info->philos[i].meal_mutex, NULL);
		info->philos[i].info = info;
		info->philos[i].id = i + 1;
		info->philos[i].time_to_die = info->time_to_die;
		info->philos[i].meals_counter = 0;
		info->philos[i].l_fork = &info->forks[i];
		if (i == 0)
			info->philos[i].r_fork = &info->forks[info->n_philos - 1];
		else
			info->philos[i].r_fork = &info->forks[i - 1];
	}
}

int	init_program(char **av, t_info *info)
{
	if (check_args(av) == 1)
		return (1);
	info->n_philos = ft_atol(av[1]);
	info->time_to_die = ft_atol(av[2]);
	info->time_to_eat = ft_atol(av[3]);
	info->time_to_sleep = ft_atol(av[4]);
	if (av[5])
	{
		info->n_meals = ft_atol(av[5]);
		if (info->n_meals <= 0)
			return (1);
	}
	else
		info->n_meals = -1;
	if (check_for_values(info) == 1)
		return (1);
	info->dead = 0;
	info->forks = malloc(sizeof(t_fork) * info->n_philos);
	info->philos = malloc(sizeof(t_philo) * info->n_philos);
	if (!info->forks || !info->philos)
		return (1);
	init_forks(info);
	pthread_mutex_init(&info->lock, NULL);
	pthread_mutex_init(&info->message, NULL);
	return (0);
}

void	run_program(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->n_philos)
	{
		pthread_create(&info->philos[i].thread, NULL, routine, \
		&info->philos[i]);
	}
	i = -1;
	while (++i < info->n_philos)
		pthread_join(info->philos[i].thread, NULL);
}

void	finish_program(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->n_philos)
	{
		pthread_mutex_destroy(&info->philos[i].meal_mutex);
		pthread_mutex_destroy(&info->forks[i].mutex);
	}
	pthread_mutex_destroy(&info->lock);
	pthread_mutex_destroy(&info->message);
	free(info->philos);
	free(info->forks);
}
