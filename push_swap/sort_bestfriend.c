/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_bestfriend.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:07:22 by brfernan          #+#    #+#             */
/*   Updated: 2024/03/22 19:26:25 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"


/*t_cost		cost_calc(t_ht *ht_a, t_ht *ht_b)
{
	t_cost min;
	
	return (min);
}*/

void sort_list(t_dlist *head)
{
	t_dlist	*t1;
	t_dlist	*t2;
	int		temp;
	
	t1 = head;
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

int find_median(t_ht *stack)
{
	int 	count;
	int		i;
	t_dlist	*temp;
	
	count = 0;
	temp = stack->head;
	sort_list(temp);
	while (temp != NULL) 
	{
		count++;
		temp = temp->next;
	}
	temp = stack->head;
	i = 0;
	while (i < count / 2)
	{
		temp = temp->next;
		i++;
	}
	if (count % 2 == 0)
		return ((temp->value + temp->prev->value) / 2);
	else
		return (temp->value);
}

void sort_bestfriend(t_ht *ht_a, t_ht *ht_b)
{
	int	median;
	while (ht_a->size > 3)
	{
		median = find_median(ht_a);
		push(ht_a, ht_b, 'b');
		/*median = find_median(ht_a);//median of a
		if (ht_a->head->value < median)
			push(ht_a, ht_b, 'b');
		else
			rotate(ht_a, 'a');*/
		/*median = find_median(ht_b->head);//median of b
		if (ht_b->head->value <= median)
			rotate(ht_b, 'b');*/
	}
	printf("median %d ", median);
	return ;
/*
	while ht_b
		push (order median)
	min = cost calc
	sort everything
	while hta value != 1
		rotate
	
*/

//	t_cost min = cost_calc(&ht_a, &ht_b);
//	printf("min cost: %d\n", min.cost);
}