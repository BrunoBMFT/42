/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:25:19 by bruno             #+#    #+#             */
/*   Updated: 2023/11/27 17:04:00 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!lst)
		return ;
	while (lst && *lst)
	{
		temp = (*lst)->next;
		if (del)
			del((*lst)->content);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}
/*#include <stdio.h>
#include <string.h>
void del(void *content)
{
    free(content);
}

int	main(void)
{
	t_list *current = malloc(sizeof(t_list));
	t_list *node1 = malloc(sizeof(t_list));
	t_list *node2 = malloc(sizeof(t_list));

    current->content = strdup("first node");
    current->next = node1;
    node1->content = strdup("second node");
    node1->next = node2;
    node2->content = strdup("third node");
    node2->next = NULL;
	ft_lstclear(&current, del);
	if (!current)
		printf("cleared");
	else
		printf("not cleared");
}*/