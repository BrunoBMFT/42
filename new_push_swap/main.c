/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:37:09 by bruno             #+#    #+#             */
/*   Updated: 2024/02/16 16:38:56 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "push_swap.h"

// * change printf to ft_printf

int main(int ac, char **av)
{
	int	i = 1;
// * NORM, instead of aStack, something like a_stack
//	t_dlist *aStack = NULL;
	t_ht 	htA;
	t_dlist *bStack = NULL;
	t_ht 	htB;
	
	htA.head = NULL;
	htA.tail = NULL;
	htB.head = NULL;
	htB.tail = NULL;
	htB.head = bStack;
	
	if (ac < 2)
		return (0);
	/*if (ac == 2) // not working with i
	{
		char	**read;
		read = ft_split(av[1], ' ');
		while (read[i])
		{
			new_node(&htA, ft_atol(read[i]));
			i++;
		}
	}*/
	else if (ac >= 2)
	{
		new_node(&htA, ft_atol(av[i]));
		i++;
		while (i < ac)
		{
			new_node(&htA, ft_atol(av[i]));
			i++;
		}
	}
//	push(&htA, &htB);
	revrotate(&htA);

	
	// TODO from here down is testing

	printf("Stack A: ");
	lst_print(&htA);
	printf("\nStack B: ");
	lst_print(&htB);
	printf("\n");
}
