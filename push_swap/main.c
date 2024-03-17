/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:37:09 by bruno             #+#    #+#             */
/*   Updated: 2024/03/17 00:17:59 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "push_swap.h"

// ! FIX MEMORY LEAKS
// TODO remove lstprint
// TODO make sort and something sort smaller and less functions
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
			if (parse_digit(av[i]) == 0 || parse_doubles(av, ft_atol(av[i]), &ht_a) == 0)
				return (ft_putstr("Error\n"));
			new_node(&ht_a, ft_atol(av[i]));
			i++;
		}
	}
	ht_a = normalizer(&ht_a);

	sort(&ht_a, &ht_b, i);
	printf("Stack A: ");
	lst_print(&ht_a);
	printf("\nStack B: ");
	lst_print(&ht_b);
	printf("\n");
	ft_lstclear(&ht_a);
	ft_lstclear(&ht_b);
}
