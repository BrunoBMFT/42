/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:37:09 by bruno             #+#    #+#             */
/*   Updated: 2024/03/16 19:39:31 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "push_swap.h"
// ! FIX MEMORY LEAKS
// TODO  change printf to ft_printf
// TODO if error display "Error" and \n, aka duplicates, not ints or bigger than int*/
// TODO remove lstprint
// TODO make sort and something sort smaller and less functions
// TODO make normalizer
// *change ht_a name

void	initiate(t_ht *ht_a, t_ht *ht_b)
{
	ht_a->head = NULL;
	ht_a->tail = NULL;
	ht_b->head = NULL;
	ht_b->tail = NULL;
	ht_a->bff = 0;
	ht_b->bff = 0;
	ht_a->smallest = 0;
	ht_b->smallest = 0;
	ht_a->size = 0;
	ht_b->size = 0;
}

int	parse_digit(char *str)//1 is only digit
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] > '0' && str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	parse_doubles(char **str, int content, t_ht *stack)//1 is no doubles
{
	int	i;

	i = 0;
	t_dlist *temp;

	temp = stack->head;
	while (str[i])
	{
		while (temp)
		{
			if (temp->value == content)
				return (free (temp), 0);
			temp = temp->next;
		}
		i++;
	}
	free (temp);
	return (1);
}

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
	sort(&ht_a, &ht_b, i);
	printf("Stack A: ");
	lst_print(&ht_a);
	printf("\nStack B: ");
	lst_print(&ht_b);
	printf("\n");
	ft_lstclear(&ht_a);
	ft_lstclear(&ht_b);
}
