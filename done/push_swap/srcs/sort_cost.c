/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_cost.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:04:00 by bruno             #+#    #+#             */
/*   Updated: 2024/05/08 18:50:18 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	cost_head_a(t_dlist *a_node, int bff)
{
	int		count;
	t_dlist	*temp_a;

	count = 0;
	temp_a = a_node;
	if (bff == INT_MAX)
		return (0);
	while (temp_a && temp_a->value != bff)
	{
		count++;
		temp_a = temp_a->next;
	}
	return (count);
}

int	cost_head_b(t_dlist *b_node, t_dlist *node)
{
	int		count;
	t_dlist	*temp_b;

	count = 0;
	temp_b = b_node;
	while (temp_b && temp_b->value != node->value)
	{
		count++;
		temp_b = temp_b->next;
	}
	return (count);
}

int	cost_tail_a(t_dlist *a_node, int bff)
{
	int		count;
	t_dlist	*temp_a;

	count = 0;
	temp_a = a_node;
	if (bff == INT_MAX)
		return (0);
	while (temp_a && temp_a->value != bff)
	{
		count++;
		temp_a = temp_a->prev;
	}
	return (count + 1);
}

int	cost_tail_b(t_dlist *b_node, t_dlist *node)
{
	int		count;
	t_dlist	*temp_b;

	count = 0;
	temp_b = b_node;
	while (temp_b && temp_b->value != node->value)
	{
		count++;
		temp_b = temp_b->prev;
	}
	return (count + 1);
}
