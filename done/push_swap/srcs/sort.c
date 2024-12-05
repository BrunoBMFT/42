/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 04:38:12 by bruno             #+#    #+#             */
/*   Updated: 2024/05/08 18:34:26 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

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
	t_dlist	*temp;

	temp = ht_a->head;
	while (temp->next)
	{
		if (temp->value > temp->next->value)
			return (0);
		temp = temp->next;
	}
	return (1);
}

void	sort(t_ht *ht_a, t_ht *ht_b)
{
	if (!is_sorted(ht_a))
	{
		if (ht_a->size == 2)
			swap(ht_a, 'a');
		else if (ht_a->size == 3)
			sort3(ht_a);
		else
			sort_bestfriend(*ht_a, *ht_b);
	}
	ft_lstclear(ht_a);
	ft_lstclear(ht_b);
	return ;
}
