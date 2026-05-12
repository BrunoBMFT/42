/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:02:36 by bruno             #+#    #+#             */
/*   Updated: 2024/05/08 18:34:20 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	push_to_b(t_ht *ht_a, t_ht *ht_b)
{
	int	median;

	while (ht_a->size > 3)
	{
		median = find_median(ht_a->head);
		if (ht_a->head->value > median)
			rotate(ht_a, 'a');
		else
			push(ht_a, ht_b, 'b');
	}
}

void	prep_push(t_ht *ht_a, t_ht *ht_b, t_cost min)
{
	if (min.direction_a == min.direction_b)
	{
		while (ht_a->head->value != min.a_node
			&& ht_b->head->value != min.b_node)
		{
			if (min.direction_a == 1)
				bothrotate(ht_a, ht_b);
			else if (min.direction_a == 0)
				bothrevrotate(ht_a, ht_b);
		}
	}
	while (ht_a->head->value != min.a_node)
	{
		if (min.direction_a == 1)
			rotate(ht_a, 'a');
		else if (min.direction_a == 0)
			revrotate(ht_a, 'a');
	}
	while (ht_b->head->value != min.b_node)
	{
		if (min.direction_b == 1)
			rotate(ht_b, 'b');
		else if (min.direction_b == 0)
			revrotate(ht_b, 'b');
	}
}

void	rotate_to_first(t_ht *ht_a)
{
	t_ht	temp;
	int		small;

	temp = *ht_a;
	small = find_small(&temp);
	while (ht_a->head->value != small)
	{
		if (cost_head_a(ht_a->head, small)
			<= cost_tail_a(ht_a->tail, small))
			rotate(ht_a, 'a');
		else if (cost_head_a(ht_a->head, small)
			> cost_tail_a(ht_a->tail, small))
			revrotate(ht_a, 'a');
	}
}
