/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_cost.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:04:00 by bruno             #+#    #+#             */
/*   Updated: 2024/03/20 17:04:10 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

//add frees to costs (??)
int	cost_head_a(t_ht ht_a, int bff)
{
	int count = 0;

	t_dlist *temp_a = ht_a.head;
	if (bff == INT_MAX)
		return (0);
	while (temp_a && temp_a->value != bff)
	{
		count++;
		temp_a = temp_a->next;
	}
	return (count);
}
int	cost_head_b(t_ht ht_b, t_dlist *node)
{
	int count = 0;

	t_dlist *temp_b = ht_b.head;
	while (temp_b && temp_b->value != node->value)
	{
		count++;
		temp_b = temp_b->next;
	}
	return (count);
}
int	cost_tail_a(t_ht ht_a, int bff)
{
	int count = 0;

	t_dlist *temp_a = ht_a.head;
	if (bff == INT_MAX)
		return (0);
	while (temp_a && temp_a->value != bff)
	{
		count++;
		temp_a = temp_a->prev;
	}
	return (count);
}
int	cost_tail_b(t_ht ht_b, t_dlist *node)
{
	int count = 0;

	t_dlist *temp_b = ht_b.head;
	while (temp_b && temp_b->value != node->value)
	{
		count++;
		temp_b = temp_b->prev;
	}
	return (count);
}
