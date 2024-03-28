/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_bestfriend.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:07:22 by brfernan          #+#    #+#             */
/*   Updated: 2024/03/28 01:07:26 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"


int	find_small(t_ht *stack)
{
	int smallest = INT_MAX;
	t_dlist	*temp = stack->head;

	while (temp)
	{
		if (temp->value < smallest)
			smallest = temp->value;
		temp = temp->next;
	}
	return (smallest);
}

int	bestfriend(t_ht ht_a, t_dlist *node_b)
{
	t_dlist	*temp;
	temp = ht_a.head;
	
	int	friend = node_b->value;
	int bestfr = INT_MAX;
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
//skips first in case that slot 1 bigger than slot 2
t_cost	cost_calc(t_ht *ht_a, t_ht *ht_b, int bff, t_dlist *node)//cost of tail needs to be +1 because of rrr
{
	t_cost total;
	t_cost a;
	t_cost b;
	a.cost = 1;
	b.cost = 1;
	int head_a = cost_head_a(ht_a->head, bff);
	int tail_a = cost_tail_a(ht_a->tail, bff) + 1;
	if (head_a <= tail_a)// <= ??
	{
		a.cost = head_a;
		total.direction_a = 1;
	}
	else 
	{
		a.cost = tail_a;
		total.direction_a = 0;
//		if (a.cost != 1)
//			a.cost++;//rra
	}
	int head_b = cost_head_b(ht_b->head, node);
	int tail_b = cost_tail_b(ht_b->tail, node) + 1;
	if (head_b <= tail_b)
	{
		b.cost = head_b;
		total.direction_b = 1;
	}
	else 
	{
		b.cost = tail_b;
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
	temp_b = ht_b.head;
	t_cost	min;
	t_cost 	cost;
	min.cost = INT_MAX;
	while (temp_b)
	{
		cost = cost_calc(&ht_a, &ht_b, bestfriend(ht_a, temp_b), temp_b);
		if (cost.cost <= min.cost)
			min = cost;
		temp_b = temp_b->next;
	}
	return (min);
}

void sort_list(t_ht *stack)
{
	t_dlist	*t1;
	t_dlist	*t2;
	int		temp;
	
	t1 = stack->head;
	while (t1->next)
	{
		t2= t1->next;
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

int find_median(t_dlist *head_a)//make better
{
	int 	count = 0;
	int		i = 0;
	int		ret;
	t_dlist	*temp = head_a;
	t_ht	lst;
	
    while (temp)
    {
        count++;
        temp = temp->next;
    }
	temp = head_a;
	lst.head = NULL;
	lst.tail = NULL;
	while (temp)
	{
		new_node(&lst, temp->value);
		temp = temp->next;
	}
	sort_list(&lst);
	while (i < count / 2)//use stack size instead of count
	{
		lst.head = lst.head->next;
		i++;
	}
	if (count % 2 == 0)
		ret = (lst.head->value + lst.head->prev->value) / 2;
	else
		ret = lst.head->value;
//	free (temp);
	ft_lstclear(&lst);
	return (ret);
}

void	sort_bestfriend(t_ht ht_a, t_ht ht_b)
{
	while (ht_a.size > 3)
	{
		if (ht_a.head->value >= find_median(ht_a.head))
			rotate(&ht_a, 'a');
		else
		{
			push(&ht_a, &ht_b, 'b');
			if (ht_b.head->value < find_median(ht_b.head))
				rotate(&ht_b, 'b');
		}
	}
	sort3(&ht_a);
	while (ht_b.head)
	{
		t_cost min = minimum_cost(ht_a, ht_b);
//if both counts are equal, make another function
		if (min.direction_a == min.direction_b)
		{
			while (ht_a.head->value != min.a_node && ht_b.head->value != min.b_node)
			{
			if (min.direction_a == 1)
				bothrotate(&ht_a, &ht_b);
			else if (min.direction_a == 0)
				bothrevrotate(&ht_a, &ht_b);
			}
		}
		while (ht_a.head->value != min.a_node)
		{
			if (min.direction_a == 1)
				rotate(&ht_a, 'a');
			else if (min.direction_a == 0)
				revrotate(&ht_a, 'a');
		}
		while (ht_b.head->value != min.b_node)
		{
			if (min.direction_b == 1)
				rotate(&ht_b, 'b');
			else if (min.direction_b == 0)
				revrotate(&ht_b, 'b');
		}
		push(&ht_b, &ht_a, 'a');
	}

	t_ht temp;
	temp = ht_a;
	int small = find_small(&temp);
	while (ht_a.head->value != small)
	{
		if (cost_head_a(ht_a.head, small) <= cost_tail_a(ht_a.head, small))
			rotate(&ht_a, 'a');
		else if (cost_head_a(ht_a.head, small) > cost_tail_a(ht_a.head, small))
			revrotate(&ht_a, 'a');
	}
	ft_lstclear(&ht_a);
	ft_lstclear(&ht_b);
}