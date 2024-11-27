/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:36:11 by bruno             #+#    #+#             */
/*   Updated: 2024/11/26 22:07:06 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, 0);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	get_int(pthread_mutex_t *mutex, int from)
{
	int	value;

	pthread_mutex_lock(mutex);
	value = from;
	pthread_mutex_unlock(mutex);
	return (value);
}

void	set_int(pthread_mutex_t *mutex, int *to_set, int value)
{
	pthread_mutex_lock(mutex);
	(*to_set) = value;
	pthread_mutex_unlock(mutex);
}

int	get_bool(pthread_mutex_t *mutex, bool from)
{
	bool	value;

	pthread_mutex_lock(mutex);
	value = from;
	pthread_mutex_unlock(mutex);
	return (value);
}

void	set_bool(pthread_mutex_t *mutex, bool *to_set, bool value)
{
	pthread_mutex_lock(mutex);
	(*to_set) = value;
	pthread_mutex_unlock(mutex);
}
