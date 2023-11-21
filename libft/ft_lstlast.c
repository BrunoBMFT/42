/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:25:25 by bruno             #+#    #+#             */
/*   Updated: 2023/10/24 17:53:09 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	while (lst)
	{
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	return (lst);
}
/*#include <stdio.h>
int	main(void)
{
	t_list *current = NULL;
	t_list *node1 = malloc(sizeof(t_list));
	t_list *node2 = malloc(sizeof(t_list));
	node1->content = "node 1";
	node1->next = node2;
	node2->content = "last";
	node2->next = NULL;
	current = node1;
	t_list *last_node = ft_lstlast(current);
	printf("%s",(char *)last_node->content);
	free (node1);
	free (node2);
}*/
