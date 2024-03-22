/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:37:09 by bruno             #+#    #+#             */
/*   Updated: 2024/03/22 17:48:42 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "push_swap.h"

// ! BROKEN NORMALIZER


// LIST START (pointer to first node)
// TODO for functions sending lists, send only the pointer to head
// TODO remove lstprint
// TODO make sort and something sort smaller and less functions
// TODO make normalizer
// TODO remove checker and visualizer
// *change ht_a name
void	normalizer(t_ht *stack)
{
	t_dlist	*temp;
	t_dlist	*temp2;
	int		count;

	temp = stack->head;
	while (temp)
	{
		count = 1;
		temp2 = stack->head;
		while (temp && temp2)
		{
			if (temp2->value < temp->value)
				count++;
			temp2 = temp2->next;
			printf("%d, ", count);
		}
		printf("\n%d\n", count);
		temp->value = count;
		temp = temp->next;
	}
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
	else if (ac >= 3)//maybe put parse digit and double here somehow
	{
		while (i < ac)
		{
			if (parse_digit(av[i]) == 0 || parse_doubles(av, ft_atol(av[i]), &ht_a) == 0)
			{
				ft_lstclear(&ht_a);
				return (ft_lstclear(&ht_a), ft_putstr("Error\n"));//i think not supposed to print, not sure
			}
			new_node(&ht_a, ft_atol(av[i]));
			i++;
		}
	}
	
//	normalizer(&ht_a);

//	ht_a.start = find_small(&ht_a);
	


	sort(&ht_a, &ht_b, i);
}
