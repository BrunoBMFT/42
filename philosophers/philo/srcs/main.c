/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 01:48:41 by bruno             #+#    #+#             */
/*   Updated: 2024/11/27 17:50:40 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int ac, char **av)
{
	t_table	table;
	t_philo	*first;

	if (!parser(ac, av, &table))
		return (1);
	first = table.philo;
	while (table.philo)
	{
		if (pthread_create(&table.philo->ptid, NULL,
				&philo_routine, table.philo))
			return (stop_sim(&table));
		table.philo = table.philo->next;
		if (table.philo == first)
			break ;
	}
	pthread_create(&table.observer, NULL, &observe_experiment, &table);
	join_threads(&table);
	return (0);
}
