/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 02:39:31 by bruno             #+#    #+#             */
/*   Updated: 2024/10/17 21:37:52 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	print_action(t_philo *philo, int action)
{
	int	time = 0;

	if (!is_sim_running(philo))//maybe not needed, test
		return ;
	pthread_mutex_lock(&philo->table->print_mutex);
	time = get_time() - philo->table->start_time;
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
	pthread_mutex_unlock(&philo->table->print_mutex);
}
