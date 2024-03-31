/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 23:31:04 by bruno             #+#    #+#             */
/*   Updated: 2024/03/31 23:57:13 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	initiate(t_ht *ht_a, t_ht *ht_b)
{
	ht_a->head = NULL;
	ht_a->tail = NULL;
	ht_b->head = NULL;
	ht_b->tail = NULL;
	ht_a->size = 0;
	ht_b->size = 0;
}

int	parse_digit(char *str)//1 is only digit
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9') && str[i] != '-')
			return (0);
		i++;
	}
	return (1);
}

int	parse_doubles(char **str, int content, t_ht *stack)//1 is no doubles
{
	t_dlist	*temp;
	int		i;

	i = 0;
	temp = stack->head;
	while (str[i])
	{
		while (temp)
		{
			if (temp->value == content)
				return (0);
			temp = temp->next;
		}
		i++;
	}
	return (1);
}

void	normalizer_aux(t_dlist *t1, t_dlist *t2, t_ht *lst, int count)
{
	while (t1)
	{
		count = 1;
		t2 = lst->head->next;
		while (t1 && t2)
		{
			if (t2->value < t1->value)
				count++;
			t2 = t2->next;
		}
		t1->value = count;
		t1 = t1->next;
	}
}

void	normalizer(t_dlist *head_a)
{
	t_dlist	*t1;
	t_dlist	*t2;
	t_ht	lst;
	int		count;

	t1 = head_a;
	lst.tail = NULL;
	lst.head = head_a;
	count = 1;
	while (t1)
	{
		new_node(&lst, t1->value);
		t1 = t1->next;
	}
	t1 = lst.head;
	t2 = lst.head->next;
	normalizer_aux(t1, t2, &lst, count);
	ft_lstclear(&lst);
}
