/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 01:48:41 by bruno             #+#    #+#             */
/*   Updated: 2024/06/11 03:41:00 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int ac, char **av)
{
//	if (!parser(ac, av))
//		return (1);
	struct timeval tv;
	time_t time;
	int num;
	scanf("%d", &num);
	gettimeofday(&tv, 0);
	printf("%d, %ld\n", num, tv.tv_sec);
	scanf("%d", &num);
	gettimeofday(&tv, 0);
	printf("%d, %ld\n", num, tv.tv_sec);

	return (0);
}
