/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_bestfriend.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:07:22 by brfernan          #+#    #+#             */
/*   Updated: 2024/03/23 01:20:20 by bruno            ###   ########.fr       */
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
	total.to_sort = node->value;
	int head_a = cost_head_a(*ht_a, bff);
	int tail_a = cost_tail_a(*ht_a, bff) + 1;
	if (head_a <= tail_a)// <= ??
	{
		a.cost = head_a;
		total.direction_a = 1;
		total.a_node = bff;
	}
	else 
	{
		a.cost = tail_a;
		a.cost--;
		total.direction_a = 0;
		if (a.cost != 1)
			a.cost++;//rra
	}
	int head_b = cost_head_b(*ht_b, node);
	int tail_b = cost_tail_b(*ht_b, node) + 1;
	if (head_b <= tail_b)
	{
		b.cost = head_b;
		total.direction_b = 1;
		b.cost++;//pa
	}
	else 
	{
		b.cost = tail_b;
		total.direction_b = 0;
		b.cost++;//rrb pa
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
	min.no_bff = 0;
//	cost = cost_calc(&ht_a, &ht_b, bestfriend(ht_a, temp_b), temp_b);//this here to make everything in min = cost
//	min = cost;
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

/*void sort_list(t_ht stack)
{
	t_ht	t1;
	t_ht	t2;
	int		temp;
	
	t1 = stack;
	while (t1.head->next)
	{
		t2.head = t1.head->next;
		while (t2.head)
		{
			if (t1.head->value > t2.head->value) 
			{
				temp = t1.head->value;
				t1.head->value = t2.head->value;
				t2.head->value = temp;
			}
			t2.head = t2.head->next;
		}
		t1.head = t1.head->next;
	}
}

int find_median(t_ht stack)
{
	int 	count;
	int		i;
	t_ht	temp;
	
	count = 0;
	temp = stack;
	sort_list(temp);
	while (temp.head != NULL) 
	{
		count++;
		temp.head = temp.head->next;
	}
	temp = stack;
	i = 0;
	while (i < count / 2)
	{
		temp.head = temp.head->next;
		i++;
	}
//	printf("%d, ", temp->value);
	if (count % 2 == 0)
		return ((temp.head->value + temp.head->prev->value) / 2);
	else
		return (temp.head->value);
}*/

//change every function to pointers
void	sort_bestfriend(t_ht ht_a, t_ht ht_b)
{
	/*// ! median not working
	int	median;
	while (ht_a.size > 3)
	{
		median = find_median(ht_a);
		printf("%d, ", ht_a.head->value);
		if (ht_a.head->value > median)
			rotate(&ht_a, 'a');
		else if (ht_a.head->value < median)
			push(&ht_a, &ht_b, 'b');
	}*/
	while (ht_a.size > 3)
		push(&ht_a, &ht_b, 'b');
	sort3(&ht_a);
	while (ht_b.head)
	{
		t_cost min = minimum_cost(ht_a, ht_b);
//if both counts are equal, make another function
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
		if (min.no_bff == 1)
			rotate(&ht_a, 'a');
	}

	t_ht temp;
	temp = ht_a;
	int small = find_small(&temp);
	while (ht_a.head->value != small)//NOT REALLY WORKING
	{
		if (cost_head_a(ht_a, small) <= cost_tail_a(ht_a, small))
			rotate(&ht_a, 'a');
		else if (cost_head_a(ht_a, small) > cost_tail_a(ht_a, small))
			revrotate(&ht_a, 'a');
	}
//	lst_print(&ht_a, 'a');
//	lst_print(&ht_b, 'b');
	ft_lstclear(&ht_a);
	ft_lstclear(&ht_b);
}