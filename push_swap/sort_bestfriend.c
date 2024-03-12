/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_bestfriend.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:07:22 by brfernan          #+#    #+#             */
/*   Updated: 2024/03/12 16:27:17 by bruno            ###   ########.fr       */
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

int	cost_calc(t_ht *ht_a, t_ht *ht_b, int bff, t_dlist *node)//cost of tail needs to be +1 because of rrr
{
	t_cost a;
	a.cost = 1;
	t_cost b;
	b.cost = 1;
	int head_a = cost_head_a(*ht_a, bff);
	int tail_a = cost_tail_a(*ht_a, bff) + 1;
	if (head_a < tail_a)
	{
		a.cost = head_a;
		a.direction = 1;
		printf("a min cost: head: %d\n", a.cost);
	}
	else 
	{
		a.cost = tail_a;
		a.direction = 0;
		printf("a min cost: tail: %d\n", a.cost);
		if (a.cost != 1)
			a.cost++;//rra
	}
	int head_b = cost_head_b(*ht_b, node);
	int tail_b = cost_tail_b(*ht_b, node) + 1;
	if (head_b < tail_b)
	{
		b.cost = head_b;
		b.direction = 1;
		printf("b min cost: head: %d\n", b.cost);
		b.cost++;//pa
	}
	else 
	{
		b.cost = tail_b;
		b.direction = 0;
		printf("b min cost: tail: %d\n", b.cost);
		b.cost++;//rrb pa
	}
	int total_cost = b.cost + a.cost;
	printf("total cost: %d", total_cost);
	return (total_cost);
}

// TODO working qb.
/*int	cost_calc(t_ht ht_a, t_ht ht_b, int bff, t_dlist *node)//cost of tail needs to be +1 because of rrr
{//separate head and tail costs (if cost head a and cost tail b are smaller, use thos)
	int cost_head = 1;
	int cost_tail = 1;
	int head_a = cost_head_a(ht_a, bff);
	int head_b = cost_head_b(ht_b, node);
	cost_head = head_a + head_b + 1;
//	printf("\thead cost: %d\n", cost_head);

	int tail_a = cost_tail_a(ht_a, bff);
	int tail_b = cost_tail_b(ht_b, node);
	cost_tail = tail_a + tail_b + 2;//+2 for rrr and pa (in the case that bff is present)
	if (cost_tail_a == 0 || cost_tail_b == 0)//2 on tail
		cost_tail += 1;
	if (cost_tail_a == 0 && cost_tail_b == 0)//2 on tail
		cost_tail += 2;
//	printf("\ttail cost: %d \n\n", cost_tail);
	if (cost_head <= cost_tail)
		return (cost_head);
	else if (cost_head > cost_tail)
		return (cost_tail);
	return (0);
}*/

t_cost	minimum_cost(t_ht ht_a, t_ht ht_b)
{
	t_ht	temp_b = ht_b;
	int 	cost;
	t_cost	min;
	min.cost = INT_MAX;
	while (temp_b.head)//fix costs (when )
	{
		printf("\nnode: %d\n", temp_b.head->value);
		temp_b.bff = bestfriend(ht_a, temp_b.head);
		cost = cost_calc(&ht_a, &ht_b, temp_b.bff, temp_b.head);
		if (cost <= min.cost)
			min.cost = cost;
		temp_b.head = temp_b.head->next;
	}
	return (min);
}

void	something_sort(t_ht ht_a, t_ht ht_b)
{
	while (ht_a.head->next->next->next)//doesnt work with 1 2 3 5 4 6 OR 1 5 2 4 3 6
	{
		push(&ht_a, &ht_b, 'b');
	}
	sort3(&ht_a);
	t_cost min = minimum_cost(ht_a, ht_b);
	printf("\nminimum cost: %d", min.cost);
}