/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 02:39:31 by bruno             #+#    #+#             */
/*   Updated: 2024/09/21 21:59:49 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	print_eating(int time, int philo)
{
	printf("%d %d is eating\n", time, philo);
}

void	print_tookfork(int time, int philo)
{
	printf("%d %d has taken a fork\n", time, philo);
}

void	print_sleeping(int time, int philo)
{
	printf("%d %d is sleeping\n", time, philo);
}

void	print_thinking(int time, int philo)
{
	printf("%d %d is thinking\n", time, philo);
}

void	print_died(int time, int philo)
{
	printf("%d %d died\n", time, philo);
}