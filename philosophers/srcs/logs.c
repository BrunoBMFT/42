/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 02:39:31 by bruno             #+#    #+#             */
/*   Updated: 2024/11/27 00:45:46 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

bool	is_sim_running(t_table *table)
{
	return (get_bool(&table->is_running_mutex,
			table->is_running));
}

void	print_action(t_philo *philo, int action)
{
	int	time;

	set_int(&philo->table->print_mutex, &time, get_time()
		- philo->table->start_time);
	if (action == DIED)
		printf("%d %d died\n", time, philo->id);
	if (!is_sim_running(philo->table))
		return ;
	if (action == TOOKFORK)
		printf("%d %d has taken a fork\n", time, philo->id);
	if (action == EATING)
		printf("%d %d is eating\n", time, philo->id);
	if (action == SLEEPING)
		printf("%d %d is sleeping\n", time, philo->id);
	if (action == THINKING)
		printf("%d %d is thinking\n", time, philo->id);
}
