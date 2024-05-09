/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   median.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 23:58:22 by bruno             #+#    #+#             */
/*   Updated: 2024/05/08 18:34:12 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	find_small(t_ht *stack)
{
	int		smallest;
	t_dlist	*temp;

	smallest = INT_MAX;
	temp = stack->head;
	while (temp)
	{
		if (temp->value < smallest)
			smallest = temp->value;
		temp = temp->next;
	}
	return (smallest);
}

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

int	find_median_aux(int i, t_dlist *temp, t_ht *lst)
{
	int	value;

	temp = lst->head;
	while (i < lst->size / 2)
	{
		temp = temp->next;
		i++;
	}
	value = temp->value;
	return (value);
}

int	find_median(t_dlist *head_a)
{
	t_ht	lst;
	t_dlist	*temp;
	int		value;
	int		i;

	temp = head_a;
	lst.tail = NULL;
	lst.head = head_a;
	lst.size = 1;
	if (!temp->next)
		return (temp->value);
	temp = temp->next;
	while (temp)
	{
		new_node(&lst, temp->value);
		temp = temp->next;
	}
	sort_list(&lst);
	i = 0;
	value = find_median_aux(i, temp, &lst);
	ft_lstclear(&lst);
	return (value);
}
