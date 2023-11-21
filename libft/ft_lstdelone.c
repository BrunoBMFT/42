/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:25:21 by bruno             #+#    #+#             */
/*   Updated: 2023/10/26 14:51:01 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	if (del)
		del(lst->content);
	free(lst);
}
/*#include <stdio.h>
#include <string.h>
void del(void *content)
{
    if (content)
        free(content);
}
int main(void)
{
    t_list *current = malloc(sizeof(t_list));
    t_list *node1 = malloc(sizeof(t_list));
    t_list *node2 = malloc(sizeof(t_list));
    current->content = strdup("First node");
    current->next = node1;
    node1->content = strdup("Second node");
    node1->next = node2;
    node2->content = strdup("Third node");
    node2->next = NULL;
    t_list *temp = current;
    t_list *prev = NULL;
    while (temp != node1) 
	{
        prev = temp;
        temp = temp->next;
    }
	if (prev)
        prev->next = temp->next;
    else
        current = temp->next;
    ft_lstdelone(node1, del);
	temp = current;
	while (temp != NULL)
	{
		printf("%s\n", (char *)temp->content);
        t_list *prev = temp;
		temp = temp->next;
        free(prev->content);
		free(prev);
	}
}*/