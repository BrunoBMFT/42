/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 04:38:12 by bruno             #+#    #+#             */
/*   Updated: 2024/03/15 23:13:44 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort3(t_ht *ht_a)
{
	if (ht_a->head->value < ht_a->head->next->value)
	{
		if (ht_a->head->value > ht_a->head->next->next->value)
			revrotate(ht_a, 'a');
		else if (ht_a->head->next->value > ht_a->head->next->next->value)
		{
			revrotate(ht_a, 'a');
			swap(ht_a, 'a');
		}
	}
	else if (ht_a->head->value > ht_a->head->next->value)
	{
		if (ht_a->head->next->value > ht_a->head->next->next->value)
		{
			rotate(ht_a, 'a');
			swap(ht_a, 'a');
		}
		else if (ht_a->head->value > ht_a->head->next->next->value)
			rotate(ht_a, 'a');
		else if (ht_a->head->value < ht_a->head->next->next->value)
			swap(ht_a, 'a');
	}

}

int	is_sorted(t_ht *ht_a)/*1 if sorted*/
{
	t_ht	temp;

	temp = *ht_a;
	while (temp.head)
	{
		if (temp.head->next && temp.head->value > temp.head->next->value)
			return (0);
		temp.head = temp.head->next;
	}
	return (1);
}

void	sort(t_ht *ht_a, t_ht *ht_b, int count)//make better
{
	if (is_sorted(ht_a))
	{
		printf ("is sorted\n");
		return ;
	}
	if (count == 4)
		sort3(ht_a);
	else
	{
		something_sort(*ht_a, *ht_b);
	}
	return ;
}

/* // TODO testing sort3 */
/*
if (ht_a->head->value < ht_a->head->next->value)// 1 2 3 || 1 3 2 || 2 3 1
	{
		if (ht_a->head->value > ht_a->head->next->next->value)// 2 3 1
		{
			printf("2 3 1\n");
			revrotate(ht_a);
		}
		else if (ht_a->head->next->value > ht_a->head->next->next->value)// 1 3 2 
		{
			printf("1 3 2\n");
			revrotate(ht_a);
			swap(ht_a);
		}
		else
		{
			printf("1 2 3\n");
		}
	}
	else if (ht_a->head->value > ht_a->head->next->value)// 3 2 1 || 3 1 2 || 2 1 3
	{
		if (ht_a->head->next->value > ht_a->head->next->next->value)// 3 2 1
		{
			printf("3 2 1\n");
			rotate(ht_a);
			swap(ht_a);
		}
		else if (ht_a->head->value > ht_a->head->next->next->value)// 3 1 2
		{
			printf("3 1 2\n");
			rotate(ht_a);
		}
		else if (ht_a->head->value < ht_a->head->next->next->value)// 2 1 3
		{
			printf("2 1 3\n");
			swap(ht_a);
		}
	}
*/