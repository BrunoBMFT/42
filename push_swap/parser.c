/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 23:31:04 by bruno             #+#    #+#             */
/*   Updated: 2024/03/18 02:12:05 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
				return (0);
			temp = temp->next;
		}
		i++;
	}
	return (1);
}