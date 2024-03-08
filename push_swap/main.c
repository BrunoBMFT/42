/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:37:09 by bruno             #+#    #+#             */
/*   Updated: 2024/03/08 17:03:36 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "push_swap.h"

/*// ! seg fault if more pushes than there are items in list
// TODO  change printf to ft_printf
// TODO separate instructons with \n only (pb \n ra)
// TODO if error display "Error" and \n, aka duplicates, not ints or bigger than int*/

int	doubles(int *stack, int to_check)//0 if no doubles
{
	int	i;

	i = 0;
	while (stack[i])
	{
		if (to_check == stack[i])
			return (1);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_ht	ht_a;
	t_ht	ht_b;
	int		i;
	char	**read;
	i = 1;
	ht_a.head = NULL;
	ht_a.tail = NULL;
	ht_b.head = NULL;
	ht_b.tail = NULL;
	if (ac < 2)
		return (0);
	if (ac == 2)/*not working with i, fix ./push 1*/
	{
		i--;
		read = ft_split(av[1], ' ');
		while (read[i])
		{
			if (!ft_isdigit(read[i][0]))/*needs to be error in case of "1a 2" and "a 1"*/
				return (ft_putstr("Error\n"));
			new_node(&ht_a, ft_atol(read[i]));
			i++;
		}
		ft_free_all(read);
	}
	else if (ac >= 2)/*this whole part can be a single function*/
	{
		while (i < ac)
		{
			if (!ft_isdigit(av[i][0]) || doubles((int *)av, (int)av[i]))
				return (ft_putstr("Error\n"));
			new_node(&ht_a, ft_atol(av[i]));
			i++;
		}
	}
	sort(&ht_a, &ht_b, i);
//	push(&ht_a, &ht_b, 'b');
//	revrotate(&ht_a, 'a');
//	rotate(&ht_a, 'a');
//	swap(&ht_a, 'a');
/*// TODO from here down is testing*/
/*	printf("Stack A: ");
	lst_print(&ht_a);
	printf("\nStack B: ");
	lst_print(&ht_b);
	printf("\n");*/
	ft_lstclear(&ht_a);
	ft_lstclear(&ht_b);
}
