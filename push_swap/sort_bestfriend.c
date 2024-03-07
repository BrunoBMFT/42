/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_bestfriend.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:07:22 by brfernan          #+#    #+#             */
/*   Updated: 2024/03/07 20:19:28 by bruno            ###   ########.fr       */
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

int	cost_head_a(t_ht ht_a, int bff)
{
	int count = 0;

	t_ht temp_a = ht_a;
	if (bff == INT_MAX)
	{
		return (0);
	}
	while (temp_a.head && temp_a.head->value != bff)
	{
		count++;
//		printf("ra, ");
		temp_a.head = temp_a.head->next;
	}
	return (count);
}
int	cost_head_b(t_ht ht_b, t_dlist *node)
{
	int count = 0;

	t_ht temp_b = ht_b;
	while (temp_b.head && temp_b.head->value != node->value)
	{
		count++;
//		printf("rb, ");
		temp_b.head = temp_b.head->next;
	}
	return (count);
}
int	cost_tail_a(t_ht ht_a, int bff)
{
	int count = 0;

	t_ht temp_a = ht_a;
	if (bff == INT_MAX)
	{
		return (0);
	}
	while (temp_a.tail && temp_a.tail->value != bff)
	{
		count++;
//		printf("rra, ");
		temp_a.tail = temp_a.tail->prev;
	}
	return (count);
}
int	cost_tail_b(t_ht ht_b, t_dlist *node)
{
	int count = 0;

	t_ht temp_b = ht_b;
	while (temp_b.tail && temp_b.tail->value != node->value)
	{
		count++;
//		printf("rrb, ");
		temp_b.tail = temp_b.tail->prev;
	}
	return (count);
}

int	cost_calc(t_ht ht_a, t_ht ht_b, int bff, t_dlist *node)//cost of tail needs to be +1 because of rrr
{//dont forget to add 1 more count because of pa
	int cost_head = 1;
	int cost_tail = 1;
	int head_a = cost_head_a(ht_a, bff);
	int head_b = cost_head_b(ht_b, node);
	cost_head = head_a + head_b + 1;//+1 for pa
	printf("\thead cost: %d\n", cost_head);
	
	int tail_a = cost_tail_a(ht_a, bff);
	int tail_b = cost_tail_b(ht_b, node);
	cost_tail = tail_a + tail_b;//+2 for rrr and pa (in the case that bff is present)
	printf("\ttail cost: %d \n\n", cost_tail);
	if (cost_head <= cost_tail)
		return (cost_head);
	else if (cost_head > cost_tail)
		return (cost_tail);
	return (0);
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
	int cost;
	while (temp_b.head)
	{
		cost = 0;
		temp_b.bff = bestfriend(ht_a, temp_b.head);
		printf("node: %d, bff: %d\n", temp_b.head->value, temp_b.bff);
//		cost += cost_head_a(ht_a, temp_b.bff);
//		cost += cost_head_b(ht_b, temp_b.head);
//		cost += cost_tail_a(ht_a, temp_b.bff);//ready to be pushed to top of a and then to rra
//		cost += cost_tail_b(ht_b, temp_b.head);
		cost = cost_calc(ht_a, ht_b, temp_b.bff, temp_b.head);
		printf("%d\n\n", cost);
		temp_b.head = temp_b.head->next;
	}
}