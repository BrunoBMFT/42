/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 01:48:41 by bruno             #+#    #+#             */
/*   Updated: 2024/06/11 18:53:14 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int ac, char **av)
{
//	if (!parser(ac, av))
//		return (1);
	
	struct timeval	time;
	gettimeofday(&time, 0);
	unsigned long s, l, u;
	s = (time.tv_sec * 1000);
	u = (time.tv_usec / 1000);
	l = s + u;
	usleep(5000000);
	
	gettimeofday(&time, 0);
	s = (time.tv_sec * 1000);
	u = (time.tv_usec / 1000);
	unsigned long num = s + u;
	num -= l;
	printf("%ld seconds", (num / 1000));
	return (0);
}
