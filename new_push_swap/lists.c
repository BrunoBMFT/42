/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:57:40 by bruno             #+#    #+#             */
/*   Updated: 2024/02/15 20:55:43 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_dlist	*ft_lstnew(int content)
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

void	new_node(t_ht *lst, int content)
{
	t_dlist *toadd = ft_lstnew(content);
	ft_lstadd_back(lst, toadd);
}

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

t_dlist *ft_lstrem_front(t_ht *lst)
{
	/*t_dlist *temp = lst->head;
	
	lst->head = temp->next;
//	lst->head->next->prev = NULL;
	return (temp);*/

	t_dlist	*temp;

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

/*void ft_lstdelone(t_dlist *lst)
{
	if (!lst)
		return;
	if (lst->content)
		free(lst->content);
	free(lst);
}*/

/*void	ft_lstclear(t_dlist **lst)
{
	t_dlist *temp;

	if (!lst)
		return;

	while (lst && *lst)
	{
		temp = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = temp;
	}

	*lst = NULL;
}*/

void lst_print(t_ht *lst)
{
	t_dlist *temp;
	
	temp = lst->head;
	while (temp)
	{
		printf("%d ", temp->content);
		temp = temp->next;
	}
}