/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 09:08:59 by brfernan          #+#    #+#             */
/*   Updated: 2023/11/28 12:12:15 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "push_swap.h"

t_dlist	*lstnew(void *content)
{
	t_dlist	*current;

	current = malloc(sizeof(t_dlist));
	if (!current)
		return (NULL);
	current->content = content;
	current->next = NULL;
	current->prev = NULL;
	return (current);
}

void	lstadd_back(t_pointer *ht, t_dlist *new)
{
	if (!ht->tail)
	{
		ht->tail = new;
		ht->head = new;
	}
	else
	{
		new->prev = ht->tail;
		ht->tail->next = new;
		ht->tail = new;
	}
}
void	lstadd_front(t_pointer *ht, t_dlist *new)
{
	if (!ht->head)
	{
		ht->tail = new;
		ht->head = new;
	}
	else
	{
		ht->head->prev = new;
		new->next = ht->head;
		ht->head = new;
	}
}

void	lstclear(t_pointer *ht) //*ht is pointer to head
{
	t_dlist	*temp;

	if (!ht)
		return ;
	while (ht->head)
	{
		temp = ht->head->next;
		free (ht->head);
		ht->head = temp;
	}
	ht->tail = NULL;
}