/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 02:39:31 by bruno             #+#    #+#             */
/*   Updated: 2024/09/28 15:54:17 by bruno            ###   ########.fr       */
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

void	print_action(int time, int philo, int action)
{
	if (action == TOOKFORK)
		printf("%d %d has taken a fork\n", time, philo);
	if (action == EATING)
		printf("%d %d is eating\n", time, philo);
	if (action == SLEEPING)
		printf("%d %d is sleeping\n", time, philo);
	if (action == THINKING)
		printf("%d %d is thinking\n", time, philo);
	if (action == DIED)
		printf("%d %d died\n", time, philo);
}