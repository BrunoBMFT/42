/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 04:38:12 by bruno             #+#    #+#             */
/*   Updated: 2024/03/16 18:43:22 by brfernan         ###   ########.fr       */
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

int	is_sorted(t_ht *ht_a)
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
		printf ("is sorted\n");//isnt supposed to print anything if sorted
		return ;//change to exit so doesnt do anything else
	}
	if (count == 3)
	{
		swap(ht_a, 'a');
		ft_lstclear(ht_a);
		ft_lstclear(ht_b);
		exit(0);
	}
	if (count == 4)
		sort3(ht_a);
	else
		something_sort(*ht_a, *ht_b);
	return ;
}