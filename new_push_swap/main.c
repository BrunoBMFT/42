/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:37:09 by bruno             #+#    #+#             */
/*   Updated: 2024/02/15 20:56:23 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "push_swap.h"

// * change printf to ft_printf

void	push(t_ht *from, t_ht *to)
{
	t_dlist *node = malloc(sizeof(t_ht));
	node->content = ft_lstrem_front(from);
	ft_lstadd_front(to, node);
}

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
	
	/*if (ac == 2)
	{
		str_args = ft_split(av[1], ' '); // ! NOT WORKING
		aStack = ft_lstnew(str_args[i]); // can make more efficient
		htA->head = aStack;
		i++;
		while (str_args[i])
		{
			new_node(aStack, av[i]);
			i++;
		}
	}*/
	if (ac >= 2)
	{
		new_node(&htA, ft_atol(av[i]));
		i++;
		while (i < ac)
		{
			new_node(&htA, ft_atol(av[i]));
			i++;
		}
	}
//	push(htA, htB);
//	printf("%s", (char *)node->content);
//	push(htA, htB); // pushes htA head to htB head
//	rotate(htA);


	// TODO from here down is testing

	printf("Stack A:");
	lst_print(&htA);
	printf("\nStack B:");
//	lst_print(htB);

}
