/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:57:40 by bruno             #+#    #+#             */
/*   Updated: 2024/02/17 04:36:28 by bruno            ###   ########.fr       */
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
	t_dlist	*toadd;

	toadd = ft_lstnew(content);
	ft_lstadd_back(lst, toadd);
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
void	lst_print(t_ht *lst)
{
	t_dlist	*temp;

	temp = lst->head;
	while (temp)
	{
		printf("%d ", temp->content);
		temp = temp->next;
	}
}
