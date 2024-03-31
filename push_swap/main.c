/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:37:09 by bruno             #+#    #+#             */
/*   Updated: 2024/03/31 23:57:28 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "push_swap.h"

// TODO for functions sending lists, send only the pointer to head
// TODO make normalizer
// *change ht_a name

int	main(int ac, char **av)
{
	t_ht	ht_a;
	t_ht	ht_b;
	int		i;

	initiate(&ht_a, &ht_b);
	i = 1;
	if (ac <= 2)
		return (0);
	else if (ac >= 3)
	{
		while (i < ac)
		{
			if (parse_digit(av[i]) == 0
				|| parse_doubles(av, ft_atol(av[i]), &ht_a) == 0
				|| ft_atol(av[i]) > INT_MAX || ft_atol(av[i]) < INT_MIN)
				return (ft_lstclear(&ht_a), ft_printf("Error\n"));
			new_node(&ht_a, ft_atol(av[i]));
			i++;
		}
	}
	sort(&ht_a, &ht_b, i);
}
