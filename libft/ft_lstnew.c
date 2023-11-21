/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:25:29 by bruno             #+#    #+#             */
/*   Updated: 2023/10/24 17:47:48 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*current;

	current = malloc(sizeof(t_list));
	if (!current)
		return (NULL);
	current->content = content;
	current->next = NULL;
	return (current);
}
/*#include <stdio.h>
int	main(void) 
{
	char	*content = "This is a list";
    t_list *current = ft_lstnew(content);
	if (!current)
		printf("no list");
	printf("new node content: %s", (char *)current->content);
	free(current);
}*/