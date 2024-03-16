/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_bestfriend.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:07:22 by brfernan          #+#    #+#             */
/*   Updated: 2024/03/16 01:37:44 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// ! something sort needs to run across ht_a.head and b.head????
// ! doesnt work when no bff

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

int	find_small(t_ht stack)
{
	int smallest = INT_MAX;
	t_ht temp = stack;

	while (temp.head)
	{
		if (temp.head->value < smallest)
			smallest = temp.head->value;
		temp.head = temp.head->next;
	}
	return (smallest);
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

t_cost	cost_calc(t_ht *ht_a, t_ht *ht_b, int bff, t_dlist *node)//cost of tail needs to be +1 because of rrr
{
	t_cost total;
	t_cost a;
	a.cost = 1;
	t_cost b;
	b.cost = 1;
	total.to_sort = node->value;
	if (bff == INT_MAX)
	{
		bff = find_small(*ht_a);
//		printf("bff: %d ", bff);
	}
	int head_a = cost_head_a(*ht_a, bff);
	int tail_a = cost_tail_a(*ht_a, bff) + 1;
	if (head_a < tail_a)// <= ??
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
	if (head_b < tail_b)
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
	cost = cost_calc(&ht_a, &ht_b, temp_b.bff, temp_b.head);//this here to make everything in min = cost
	min = cost;
	min.cost = INT_MAX;
	while (temp_b.head)
	{
//		printf("node: %d\n", temp_b.head->value);
		temp_b.bff = bestfriend(ht_a, temp_b.head);
		cost = cost_calc(&ht_a, &ht_b, temp_b.bff, temp_b.head);
		if (cost.cost <= min.cost)
		{
			min = cost;
		}
		temp_b.head = temp_b.head->next;
	}
	return (min);
}

void	something_sort(t_ht ht_a, t_ht ht_b)
{
	while (ht_a.size > 3)
		push(&ht_a, &ht_b, 'b');
	sort3(&ht_a);
//	t_cost min = minimum_cost(ht_a, ht_b);
//	printf("\nminimum cost: %d\n", min.cost);
//	printf("a direction: %d\n", min.direction_a);
//	printf("b direction: %d\n", min.direction_b);
//	printf("a count: %d\n", min.a_count);
//	printf("b count: %d\n", min.b_count);
	
	while (ht_b.head)
	{
		t_cost min = minimum_cost(ht_a, ht_b);//needs to move along ht_a and ht_b (??????)(in hindsight, maybe not needed to move along)
		if (min.direction_a == 1)
		{
			while (min.a_count > 0)
			{
				rotate(&ht_a, 'a');
				min.a_count--;
			}
		}
		else if (min.direction_a == 0)
		{
			while (min.a_count > 0)
			{
				revrotate(&ht_a, 'a');
				min.a_count--;
			}
		}
		if (min.direction_b == 1)
		{
			while (min.b_count > 0)
			{
				rotate(&ht_b, 'b');
				min.b_count--;
			}
		}
		else if (min.direction_b == 0)
		{
			while (min.b_count > 0)
			{
				revrotate(&ht_b, 'b');
				min.b_count--;
			}
		}
		push(&ht_b, &ht_a, 'a');
	}
	int small = find_small(ht_a);
	while (ht_a.head->value != small)
	{
		if (cost_head_a(ht_a, small) < cost_tail_a(ht_a, small))
		{
			rotate(&ht_a, 'a');
		}
		else if (cost_head_a(ht_a, small) > cost_tail_a(ht_a, small))
		{
			revrotate(&ht_a, 'a');
		}
	}
}