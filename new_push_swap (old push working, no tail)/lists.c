/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:57:40 by bruno             #+#    #+#             */
/*   Updated: 2024/01/16 19:14:51 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_dlist	*ft_lstnew(void *content)
{
	t_dlist	*current;

	current = malloc(sizeof(t_dlist));
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


t_dlist	*ft_lstlast(t_dlist *lst)
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


void	ft_lstadd_front(t_dlist **lst, t_dlist *new)
{
	t_dlist	*temp;

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


void	ft_lstadd_back(t_dlist **lst, t_dlist *new)
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


void ft_lstdelone(t_dlist *lst)
{
    if (!lst)
        return;
    if (lst->content)
        free(lst->content);
    free(lst);
}
/*#include <stdio.h>
#include <string.h>
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


void	ft_lstclear(t_dlist **lst)
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
}
/*#include <stdio.h>
#include <string.h>
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
