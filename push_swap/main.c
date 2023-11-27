/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 02:41:43 by bruno             #+#    #+#             */
/*   Updated: 2023/11/27 18:23:37 by brfernan         ###   ########.fr       */
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

t_dlist	lstadd_back(t_pointer *ht, t_dlist *new)
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
t_dlist	lstadd_front(t_pointer *ht, t_dlist *new)
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

void	lstclear(t_pointer *ht)
{
	t_list	*temp;

	if (!ht)
		return ;
	while (ht && *ht)
	{
		temp = (*ht)->next;
		free(*ht);
		*ht = temp;
	}
	*ht = NULL;
}

int	main(int argc, char **argv)
{
	t_pointer lst;
	lst.head->content;
	lst.tail->content;
	int	i;

	i = 0;
	if (argc < 2)
		return (0);//check return null		return (NULL);
	current->content = content;
}
