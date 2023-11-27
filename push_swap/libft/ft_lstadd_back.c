/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:25:13 by bruno             #+#    #+#             */
/*   Updated: 2023/11/27 15:52:08 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (*lst)
		ft_lstlast(*lst)->next = new;
	else
		*lst = new;
}
/*#include <stdio.h>
int	main(void)
{
	t_list *current = NULL;
	t_list *listtoadd = NULL;
	t_list *node1 = malloc(sizeof(t_list));
	t_list *node2 = malloc(sizeof(t_list));
	node1->content = "hello ";
	node1->next = node2;
	node2->content = "im ";
	node2->next = NULL;
	t_list *toadd = malloc(sizeof(t_list));
	toadd->content = "dead ";
	toadd->next = NULL;
	ft_lstadd_back(&current, toadd);
	t_list *temp = current;
	while (temp != NULL)
	{
		printf("%s", (char *)temp->content);
		temp = temp->next;
	}
	free(node1);
	free(node2);
	free(toadd);
}*/
