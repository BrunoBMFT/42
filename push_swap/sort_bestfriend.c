/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_bestfriend.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:07:22 by brfernan          #+#    #+#             */
/*   Updated: 2024/03/07 18:05:08 by bruno            ###   ########.fr       */
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

int	cost_head(t_ht ht_a, t_ht ht_b, t_dlist *node)//node incorrect
{
	int count = 0;

	t_ht temp_a = ht_a;
	while (temp_a.head->value != ht_b.bff)
	{
		count++;
		printf("ra, ");
		temp_a.head = temp_a.head->next;
	}
	temp_a = ht_b;
	return (count);
}

/*int	cost_calc(t_ht ht_a, t_ht ht_b, t_dlist *node)
{
	ht_b.bff = bestfriend(ht_a, node);
	printf("%d's bff: %d", node->value, ht_b.bff);
	
	int head = cost_head(ht_a, ht_b, node);
	printf("cost: %d\n", head);
	
	ht_b.head->value = 1;
	return (1);
}*/

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
		int cost = cost_head(ht_a, _b, temp_b.head);
		printf("cost to head: %d\n", cost);
//		cost_calc(ht_a, ht_b, temp_b.head);
//		printf("%d bff is %d\n", temp_b.head->value, temp_b.bff);
		temp_b.head = temp_b.head->next;
	}
}