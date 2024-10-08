/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 02:39:31 by bruno             #+#    #+#             */
/*   Updated: 2024/10/08 21:10:53 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	print_action(t_philo *philo, int action)
{
	int	time;

	time = time_since_start(philo);
	//print mutexes?
	if (action == TOOKFORK)
		printf("%d %d has taken a fork\n", time, philo->id);
	if (action == EATING)
		printf("%d %d is eating\n", time, philo->id);
	if (action == SLEEPING)
		printf("%d %d is sleeping\n", time, philo->id);
	if (action == THINKING)
		printf("%d %d is thinking\n", time, philo->id);
	if (action == DIED)
		printf("%d %d died\n", time, philo->id);
}