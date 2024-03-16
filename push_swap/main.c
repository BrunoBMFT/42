/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:37:09 by bruno             #+#    #+#             */
/*   Updated: 2024/03/16 13:59:19 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "push_swap.h"
// ! FIX MEMORY LEAKS
// ! seg fault if more pushes than there are items in list
// TODO  change printf to ft_printf
// TODO if error display "Error" and \n, aka duplicates, not ints or bigger than int*/
// TODO remove lstprint
// TODO make sort and something sort smaller and less functions
// TODO make normalizer

void	initiate(t_ht *ht_a, t_ht *ht_b)
{
	ht_a->head = NULL;
	ht_a->tail = NULL;
	ht_b->head = NULL;
	ht_b->tail = NULL;
	ht_a->size = 0;
	ht_b->size = 0;
}
int	main(int ac, char **av)
{
	t_ht	ht_a;
	t_ht	ht_b;
	int		i;
	char	**read;
	
	initiate(&ht_a, &ht_b);
	i = 1;
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
			if (!ft_isdigit(av[i][0]))
				return (ft_putstr("Error\n"));
			new_node(&ht_a, ft_atol(av[i]));
			i++;
		}
	}
	sort(&ht_a, &ht_b, i);

// TODO from here down is testing
	/*printf("Stack A: ");
	lst_print(&ht_a);
	printf("\nStack B: ");
	lst_print(&ht_b);
	printf("\n");*/
	ft_lstclear(&ht_a);
	ft_lstclear(&ht_b);
}
