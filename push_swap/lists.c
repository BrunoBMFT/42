/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:57:40 by bruno             #+#    #+#             */
/*   Updated: 2024/03/02 16:37:10 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_dlist	*ft_lstnew(int value)
{
	t_dlist	*current;

	current = malloc(sizeof(t_dlist));
	if (!current)
		return (NULL);
	current->value = value;
	current->next = NULL;
	current->prev = NULL;
	return (current);
}

void	new_node(t_ht *lst, int value)
{
	t_dlist	*toadd;

	toadd = ft_lstnew(value);
	ft_lstadd_back(lst, toadd);
}

/*void ft_lstdelone(t_dlist *lst)
{
	if (!lst)
		return;
	if (lst->value)
		free(lst->value);
	free(lst);
}*/

void	ft_lstclear(t_ht *ht_a)
{
	t_dlist	*temp;

	if (!ht_a)
		return ;
	while (ht_a->head)
	{
		temp = ht_a->head->next;
		free(ht_a->head);
		ht_a->head = temp;
	}
	ht_a->head = NULL;
}

void	lst_print(t_ht *lst)
{
	t_dlist	*temp;

	temp = lst->head;
	while (temp)
	{
		printf("%d ", temp->value);
		temp = temp->next;
	}
}
