/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:25:28 by bruno             #+#    #+#             */
/*   Updated: 2023/10/26 15:38:19 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*first;
	t_list	*new;
	t_list	*temp;

	if (!f || !del)
		return (NULL);
	first = NULL;
	while (lst)
	{
		temp = ((*f)(lst->content));
		new = ft_lstnew(temp);
		if (!new)
		{
			(*del)(temp);
			ft_lstclear(&first, (del));
			return (NULL);
		}
		ft_lstadd_back(&first, new);
		lst = lst->next;
	}
	return (first);
}
/*#include <stdio.h>
void *add_one(void *content)
{
    int *num = (int *)content;
    int *result = malloc(sizeof(int));
    *result = (*num) + 1;
    return result;
}
void del(void *content)
{
    free(content);
}
int main(void)
{
    t_list *current = malloc(sizeof(t_list));
    t_list *node1 = malloc(sizeof(t_list));
    t_list *node2 = malloc(sizeof(t_list));
    int *num1 = malloc(sizeof(int));
    *num1 = 1;
    int *num2 = malloc(sizeof(int));
    *num2 = 2;
    int *num3 = malloc(sizeof(int));
    *num3 = 3;
    current->content = num1;
    current->next = node1;
    node1->content = num2;
    node1->next = node2;
    node2->content = num3;
    node2->next = NULL;
    t_list *new_list = ft_lstmap(current, add_one, del);
    t_list *temp = new_list;
    while (temp != NULL)
    {
        printf("%d\n", *((int *)temp->content));
        temp = temp->next;
	}
    while (new_list != NULL)
    {
        temp = new_list;
        new_list = new_list->next;
        free(temp->content);
        free(temp);
    }
    free(current);
    free(node1);
    free(node2);
}*/