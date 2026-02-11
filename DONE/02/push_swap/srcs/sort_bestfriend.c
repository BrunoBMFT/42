/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_bestfriend.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:07:22 by brfernan          #+#    #+#             */
/*   Updated: 2024/05/08 18:50:07 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	bestfriend(t_ht ht_a, t_dlist *node_b)
{
	t_dlist	*temp;
	int		friend;
	int		bestfr;

	temp = ht_a.head;
	friend = node_b->value;
	bestfr = INT_MAX;
	while (temp)
	{
		if (friend < temp->value && temp->value < bestfr)
			bestfr = temp->value;
		temp = temp->next;
	}
	if (bestfr == INT_MAX)
		bestfr = find_small(&ht_a);
	return (bestfr);
}

void	cost_calc_aux(t_ht *ht_a, t_cost *a, t_cost *total, int bff)
{
	if (cost_head_a(ht_a->head, bff) <= cost_tail_a(ht_a->tail, bff))
	{
		a->cost = cost_head_a(ht_a->head, bff);
		total->direction_a = 1;
	}
	else
	{
		a->cost = cost_tail_a(ht_a->tail, bff);
		total->direction_a = 0;
	}
}

t_cost	cost_calc(t_ht *ht_a, t_ht *ht_b, int bff, t_dlist *node)
{
	t_cost	total;
	t_cost	a;
	t_cost	b;

	a.cost = 1;
	b.cost = 1;
	cost_calc_aux(ht_a, &a, &total, bff);
	if (cost_head_b(ht_b->head, node) <= cost_tail_b(ht_b->tail, node))
	{
		b.cost = cost_head_b(ht_b->head, node);
		total.direction_b = 1;
	}
	else
	{
		b.cost = cost_tail_b(ht_b->tail, node);
		total.direction_b = 0;
	}
	total.a_node = bff;
	total.b_node = node->value;
	total.cost = b.cost + a.cost;
	return (total);
}

t_cost	minimum_cost(t_ht ht_a, t_ht ht_b)
{
	t_dlist	*temp_b;
	t_cost	min;
	t_cost	cost;

	temp_b = ht_b.head;
	min.cost = INT_MAX;
	while (temp_b)
	{
		cost = cost_calc(&ht_a, &ht_b, bestfriend(ht_a, temp_b), temp_b);
		if (cost.cost < min.cost)
			min = cost;
		temp_b = temp_b->next;
	}
	return (min);
}

void	sort_bestfriend(t_ht ht_a, t_ht ht_b)
{
	t_cost	min;

	push_to_b(&ht_a, &ht_b);
	sort3(&ht_a);
	while (ht_b.head)
	{
		min = minimum_cost(ht_a, ht_b);
		prep_push(&ht_a, &ht_b, min);
		push(&ht_b, &ht_a, 'a');
	}
	rotate_to_first(&ht_a);
	ft_lstclear(&ht_a);
	ft_lstclear(&ht_b);
	exit (0);
}
