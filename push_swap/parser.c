/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 23:31:04 by bruno             #+#    #+#             */
/*   Updated: 2024/03/17 00:30:16 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*t_ht	normalizer(t_ht *stack)
{
	t_ht	normal;
	int i;
	int count;

	i = 0;
	count = 1;
	normal = *stack;
	while (normal.head)
	{
		i = normal.head->value;
		while (normal.head)
		{
			if (i > normal.head->value)
				count++;
			normal.head->value;
		}
		normal.head->value = count;
		normal.head = normal.head->next;
	}
	return (normal);
}

	t_dlist	*temp;
	t_dlist	*temp2;
	int		count;

	temp = stack->head;
	while (temp)
	{
		count = 1;
		temp2 = stack->head;
		while (temp2)
		{
			if (temp2->nbr < temp->nbr)
				count++;
			temp2 = temp2->next;
		}
		temp->value = count;
		temp = temp->next;
	}*/

void	initiate(t_ht *ht_a, t_ht *ht_b)
{
	ht_a->head = NULL;
	ht_a->tail = NULL;
	ht_b->head = NULL;
	ht_b->tail = NULL;
	ht_a->bff = 0;
	ht_b->bff = 0;
	ht_a->smallest = 0;
	ht_b->smallest = 0;
	ht_a->size = 0;
	ht_b->size = 0;
}

int	parse_digit(char *str)//1 is only digit
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] > '0' && str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	parse_doubles(char **str, int content, t_ht *stack)//1 is no doubles
{
	int	i;

	i = 0;
	t_dlist *temp;

	temp = stack->head;
	while (str[i])
	{
		while (temp)
		{
			if (temp->value == content)
				return (free (temp), 0);
			temp = temp->next;
		}
		i++;
	}
	free (temp);
	return (1);
}