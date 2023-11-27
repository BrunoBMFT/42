/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:10:31 by bruno             #+#    #+#             */
/*   Updated: 2023/11/27 15:43:44 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	*lst = new;
	new->next = temp;
}
/*#include <stdio.h>
int	main(void)
{
	t_list *current = NULL;
	t_list *node1 = malloc(sizeof(t_list));
	node1->content = "hi";
	ft_lstadd_front(&current, node1);
	while (current != NULL)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}
	free (node1);
}*/
