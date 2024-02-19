/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 04:38:12 by bruno             #+#    #+#             */
/*   Updated: 2024/02/19 21:28:09 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void sort3(t_ht *ht_a)
{
	if (ht_a->head->content < ht_a->head->next->content)
	{
		if (ht_a->head->content > ht_a->head->next->next->content)
			revrotate(ht_a);
		else if (ht_a->head->next->content > ht_a->head->next->next->content)
		{
			revrotate(ht_a);
			swap(ht_a);
		}
	}
	else if (ht_a->head->content > ht_a->head->next->content)
	{
		if (ht_a->head->next->content > ht_a->head->next->next->content)
		{
			rotate(ht_a);
			swap(ht_a);
		}
		else if (ht_a->head->content > ht_a->head->next->next->content)
			rotate(ht_a);
		else
			swap(ht_a);
	}
}

void	sort(t_ht *ht_a, t_ht *ht_b, int count)
{
	if (count == 4)
		sort3(ht_a);
	ht_b->head = NULL;
}


// TODO testing sort3
/*if (ht_a->head->content < ht_a->head->next->content)// 1 2 3 || 1 3 2 || 2 3 1
	{
		if (ht_a->head->content > ht_a->head->next->next->content)// 2 3 1
		{
			printf("2 3 1\n");
			revrotate(ht_a);
		}
		else if (ht_a->head->next->content > ht_a->head->next->next->content)// 1 3 2 
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
	else if (ht_a->head->content > ht_a->head->next->content)// 3 2 1 || 3 1 2 || 2 1 3
	{
		if (ht_a->head->next->content > ht_a->head->next->next->content)// 3 2 1
		{
			printf("3 2 1\n");
			rotate(ht_a);
			swap(ht_a);
		}
		else if (ht_a->head->content > ht_a->head->next->next->content)// 3 1 2
		{
			printf("3 1 2\n");
			rotate(ht_a);
		}
		else if (ht_a->head->content < ht_a->head->next->next->content)// 2 1 3
		{
			printf("2 1 3\n");
			swap(ht_a);
		}
	}*/