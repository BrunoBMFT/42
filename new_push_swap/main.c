/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:37:09 by bruno             #+#    #+#             */
/*   Updated: 2024/02/17 04:25:34 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "push_swap.h"

/* * change printf to ft_printf
* NORM, instead of aStack, something like a_stack*/

int	main(int ac, char **av)
{
	t_ht	ht_a;
	t_dlist	*b_stack;
	t_ht	ht_b;
	int		i;
//	t_dlist *a_stack = NULL;

	i = 1;
	b_stack = NULL;
	ht_a.head = NULL;
	ht_a.tail = NULL;
	ht_b.head = NULL;
	ht_b.tail = NULL;
	ht_b.head = b_stack;
	if (ac < 2)
		return (0);
	/*if (ac == 2) // not working with i
	{
		char	**read;
		read = ft_split(av[1], ' ');
		while (read[i])
		{
			new_node(&ht_a, ft_atol(read[i]));
			i++;
		}
	}*/
	else if (ac >= 2)
	{
		new_node(&ht_a, ft_atol(av[i]));
		i++;
		while (i < ac)
		{
			new_node(&ht_a, ft_atol(av[i]));
			i++;
		}
	}
//	push(&ht_a, &ht_b);
//	revrotate(&ht_a);
//	rotate(&ht_a);
	swap(&ht_a);
// TODO from here down is testing
	printf("Stack A: ");
	lst_print(&ht_a);
	printf("\nStack B: ");
	lst_print(&ht_b);
	printf("\n");
}
