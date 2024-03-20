/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_bestfriend.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:07:22 by brfernan          #+#    #+#             */
/*   Updated: 2024/03/20 17:59:07 by bruno            ###   ########.fr       */
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

/*bool	is_biggest(t_ht *stack)
{
	int current = stack->head->value;
	t_dlist	*temp = stack->head;

	while (temp)
	{
		if (temp->value > current)
			return (0);
		temp = temp->next;
	}
	return (1);
}*/

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
	if (bestfr == INT_MAX)
		bestfr = find_small(&ht_a);
	return (bestfr);
}
//skips first in case that slot 1 bigger than slot 2
t_cost	cost_calc(t_ht *ht_a, t_ht *ht_b, int bff, t_dlist *node)//cost of tail needs to be +1 because of rrr
{
	t_cost total;
	t_cost a;
	a.cost = 1;
	t_cost b;
	b.cost = 1;
	total.to_sort = node->value;
	int head_a = cost_head_a(*ht_a, bff);
	int tail_a = cost_tail_a(*ht_a, bff) + 1;
	if (head_a <= tail_a)// <= ??
	{
		a.cost = head_a;
		total.direction_a = 1;
		total.a_count = a.cost;
	}
	else 
	{
		a.cost = tail_a;
		total.direction_a = 0;
		total.a_count = a.cost;
		if (a.cost != 1)
			a.cost++;//rra
	}
	int head_b = cost_head_b(*ht_b, node);
	int tail_b = cost_tail_b(*ht_b, node) + 1;
	if (head_b <= tail_b)
	{
		b.cost = head_b;
		total.direction_b = 1;
		total.b_count = b.cost;
		b.cost++;//pa
	}
	else 
	{
		b.cost = tail_b;
		total.direction_b = 0;
		total.b_count = b.cost;
		b.cost++;//rrb pa
	}
	total.cost = b.cost + a.cost;
	return (total);
}

t_cost	minimum_cost(t_ht ht_a, t_ht ht_b)
{
	t_ht	temp_b = ht_b;
	t_cost	min;
	t_cost 	cost;
	min.no_bff = 0;
	cost = cost_calc(&ht_a, &ht_b, temp_b.bff, temp_b.head);//this here to make everything in min = cost
	min = cost;
	min.cost = INT_MAX;
	while (temp_b.head)
	{
		temp_b.bff = bestfriend(ht_a, temp_b.head);
		cost = cost_calc(&ht_a, &ht_b, temp_b.bff, temp_b.head);
		if (cost.cost <= min.cost)
			min = cost;
		temp_b.head = temp_b.head->next;
	}
	ft_lstclear(&temp_b);
	return (min);
}

void	something_sort(t_ht ht_a, t_ht ht_b)
{
	while (ht_a.size > 3)
		push(&ht_a, &ht_b, 'b');
	sort3(&ht_a);
	while (ht_b.head)//improve: while loop before if dir condition, so save a while loop
	{
		t_cost min = minimum_cost(ht_a, ht_b);
//		printf("node: %d ", min.to_sort);
		/*if (min.direction_a == min.direction_b)
		{
			if (min.direction_a == 1)
			{
				while (min.a_count > 0 && min.b_count > 0)
				{
					bothrotate(ht_a, ht_b);
					min.a_count--;
					min.b_count--;
				}
			}
			if (min.direction_a == 0)
			{
				while (min.a_count > 0 && min.b_count > 0)
				{
					bothrevrotate(ht_a, ht_b);
					min.a_count--;
					min.b_count--;
				}
			}
		}*/		
		
		while (min.a_count > 0)
		{
			if (min.direction_a == 1)
				rotate(&ht_a, 'a');
			else if (min.direction_a == 0)
				revrotate(&ht_a, 'a');
			min.a_count--;
		}
		while (min.b_count > 0)
		{
			if (min.direction_b == 1)
				rotate(&ht_b, 'b');
			else if (min.direction_b == 0)
				revrotate(&ht_b, 'b');
			min.b_count--;
		}
		push(&ht_b, &ht_a, 'a');
		if (min.no_bff == 1)
		{
			rotate(&ht_a, 'a');
			printf("nobff");
		}
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
//	printf("\n");
	/*if (!is_sorted(&ht_a))//! REMOVE THERE SHOULD BE NO NEED TO RUN AGAN
		something_sort(ht_a, ht_b);
	else
	{
		printf("B");
		ft_lstclear(&ht_a);
		ft_lstclear(&ht_b);
	}*/
//		printf("C");
	ft_lstclear(&ht_a);
	ft_lstclear(&ht_b);
}