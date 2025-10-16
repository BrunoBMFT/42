/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 04:35:39 by bruno             #+#    #+#             */
/*   Updated: 2024/05/08 18:34:08 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_lstadd_front(t_ht *lst, t_dlist *new)
{
	if (!lst->head)
	{
		lst->head = new;
		lst->tail = new;
		return ;
	}
	new->next = lst->head;
	lst->head->prev = new;
	lst->head = new;
}

void	ft_lstadd_back(t_ht *lst, t_dlist *new)
{
	new->next = NULL;
	if (!lst->tail)
	{
		lst->head = new;
		lst->tail = new;
		return ;
	}
	new->prev = lst->tail;
	lst->tail->next = new;
	lst->tail = new;
}

t_dlist	*ft_lstrem_front(t_ht *lst)
{
	t_dlist	*temp;

	if (!lst->head)
		return (NULL);
	temp = lst->head;
	if (temp->next)
	{
		lst->head = temp->next;
		temp->next->prev = NULL;
	}
	else
	{
		lst->head = NULL;
		lst->tail = NULL;
	}
	temp->next = NULL;
	temp->prev = NULL;
	return (temp);
}

t_dlist	*ft_lstrem_back(t_ht *lst)
{
	t_dlist	*temp;

	if (!lst->head)
		return (NULL);
	temp = lst->tail;
	if (temp->prev)
	{
		lst->tail = temp->prev;
		temp->prev->next = NULL;
	}
	else
	{
		lst->head = NULL;
		lst->tail = NULL;
	}
	temp->prev = NULL;
	temp->next = NULL;
	return (temp);
}

void	bothrevrotate(t_ht *ht_a, t_ht *ht_b)
{
	revrotate(ht_a, 'r');
	revrotate(ht_b, 'r');
	ft_printf("rrr\n");
}
