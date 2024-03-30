/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:02:36 by bruno             #+#    #+#             */
/*   Updated: 2024/03/30 18:11:42 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_list(t_ht *stack)
{
	t_dlist	*t1;
	t_dlist	*t2;
	int		temp;

	t1 = stack->head;
	while (t1->next)
	{
		t2 = t1->next;
		while (t2)
		{
			if (t1->value > t2->value)
			{
				temp = t1->value;
				t1->value = t2->value;
				t2->value = temp;
			}
			t2 = t2->next;
		}
		t1 = t1->next;
	}
}

int	find_median(t_dlist *head_a)
{
	t_ht	lst;
	t_dlist	*temp;

	temp = head_a;
	
	lst.tail = NULL;
	lst.head = head_a;
	lst.size = 1;
	if (!temp->next)
	{
		return (temp->value);
	}

	temp = temp->next;
	while (temp)
	{		
		new_node(&lst, temp->value);
		temp = temp->next;
	}
	sort_list(&lst);
	int i = 0;
	temp = lst.head;
	while (i < lst.size / 2)
	{
		temp = temp->next;
		i++;
	}
	int value = temp->value;
	ft_lstclear(&lst);
//	ft_putnbr(value);
	return (value);
}

void	push_to_b(t_ht *ht_a, t_ht *ht_b)
{
	int median;
	while (ht_a->size > 3)
	{
		median = find_median(ht_a->head);
		if (ht_a->head->value >= median)
			rotate(ht_a, 'a');
		else
		{
			push(ht_a, ht_b, 'b');
//			ft_putstr("heeeeeeeeeee");
//			median = find_median(ht_b->head);
//			if (ht_b->head->value >= median)
//				rotate(ht_b, 'b');
		}
	}
}

void	prep_push(t_ht *ht_a, t_ht *ht_b, t_cost min)
{
	if (min.direction_a == min.direction_b)
	{
		while (ht_a->head->value != min.a_node && ht_b->head->value != min.b_node)
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
		if (cost_head_a(ht_a->head, small) <= cost_tail_a(ht_a->head, small))
			rotate(ht_a, 'a');
		else if (cost_head_a(ht_a->head, small) > cost_tail_a(ht_a->head, small))
			revrotate(ht_a, 'a');
	}
}
