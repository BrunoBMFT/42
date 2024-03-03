/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_bestfriend.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:07:22 by brfernan          #+#    #+#             */
/*   Updated: 2024/03/03 20:05:34 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	bestfriend(t_ht ht_a, t_dlist *node_b)
{
	t_ht	temp = ht_a;
	
	int	friend = node_b->value;
	int bestfr = INT_MAX;
	while (temp.head)
	{
		if (friend < temp.head->value && temp.head->value < bestfr)
			bestfr = temp.head->value;
		temp.head = temp.head->next;
	}
	return (bestfr);
}

int	cost_calc(t_ht ht_a, t_ht ht_b, t_dlist *node)
{
	printf("node: %d, ", ht_b.head->value);
	ht_b.bff = bestfriend(ht_a, node);
	printf("bf: %d, ", ht_b.bff);
	t_ht temp_a = ht_a;
	t_ht temp_b = ht_b;
	int	cost = 1;
	while (temp_a.head->value != ht_b.bff)
	{
		printf("a shift, ");
		temp_a.head = temp_a.head->next;
		cost++;
	}
	while (temp_b.head != node)
	{
		printf("b shift, ");
		temp_b.head = temp_b.head->next;
		cost++;
	}
	return (cost);
}

void	something_sort(t_ht ht_a, t_ht ht_b)
{
	while (ht_a.head->next->next->next)
	{
		push(&ht_a, &ht_b, 'b');
	}
	sort3(&ht_a);
	/*printf("3 left\n");
	printf("3 sorted\n");*/
	t_ht	temp_b = ht_b;
	while (temp_b.head)
	{
		printf("cost: %d \n", cost_calc(ht_a, temp_b, temp_b.head));//not shifting through ht_b
		temp_b.head = temp_b.head->next;
	}
}