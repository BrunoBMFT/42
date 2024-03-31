/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:37:09 by bruno             #+#    #+#             */
/*   Updated: 2024/03/31 19:47:36 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "push_swap.h"

// TODO for functions sending lists, send only the pointer to head
// TODO make normalizer
// *change ht_a name
void	normalizer(t_dlist *head_a)
{
	t_dlist	*t1;
	t_dlist	*t2;
	t_ht	lst;
	int		count;

	t1 = head_a;
	lst.tail = NULL;
	lst.head = head_a;
	while (t1)
	{		
		new_node(&lst, t1->value);
		t1 = t1->next;
	}
	t1 = lst.head;
	while (t1)
	{
		count = 1;
		t2 = lst.head->next;
		while (t1 && t2)
		{
			if (t2->value < t1->value)
				count++;
			t2 = t2->next;
		}
		t1->value = count;
		t1 = t1->next;
	}
	ft_lstclear(&lst);
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
			{
				ft_lstclear(&ht_a);
				/*i think not supposed to print, not sure*/
				return (ft_lstclear(&ht_a), ft_printf("Error\n"));
			}
			new_node(&ht_a, ft_atol(av[i]));
			i++;
		}
	}
	normalizer(ht_a.head);
	sort(&ht_a, &ht_b, i);
}
