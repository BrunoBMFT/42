/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:25:23 by bruno             #+#    #+#             */
/*   Updated: 2023/10/24 18:06:10 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!f)
		return ;
	while (lst)
	{
		(*f)(lst->content);
		lst = lst->next;
	}
}
/*#include <stdio.h>
void	print_content(void *content)
{
	printf("%s\n", (char *)content);
}

int	main(void)
{
	t_list *current = malloc(sizeof(t_list));
	t_list *node1 = malloc(sizeof(t_list));
	t_list *node2 = malloc(sizeof(t_list));
	current->content = "hello";
	current->next = node1;
	node1->content = "hi";
	node1->next = node2;
	node2->content = "yo";
	node2->next = NULL;
	ft_lstiter(current, print_content);
}*/
