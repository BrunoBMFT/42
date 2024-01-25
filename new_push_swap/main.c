/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:37:09 by bruno             #+#    #+#             */
/*   Updated: 2024/01/25 18:06:26 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "push_swap.h"

void	newNode(t_dlist *aStack, char *content)
{
	t_dlist *nodetoadd = ft_lstnew(content);
	ft_lstadd_back(&aStack, nodetoadd);
}

void	push(t_dlist **from, t_dlist **to)
{
	if (!*from)
		return;
	t_dlist *temp = *from;
	*from = temp->next;
	temp->next = *to;
	if (*to)
		(*to)->prev = temp;
	temp->prev = NULL;
	*to = temp;
}

void	rotateA(t_dlist *aStack, t_dlist **headA)
{
	t_dlist *temp = *headA;
	ft_lstadd_back(&aStack, temp);
	// ! doesnt work
}

int main(int argc, char* argv[])
{
	int	i = 1;
	t_dlist *aStack = NULL;
	t_dlist **headA = &aStack;
	t_dlist *bStack = NULL;
	t_dlist **headB = &bStack;
	if (argc >= 2)
	{
		aStack = ft_lstnew(argv[i]);
		i++;
		while (i < argc)
		{
			newNode(aStack, argv[i]);
			i++;
		}
	}
	push(headA, headB); //specify on the prints if it's pushb or pusha
	rotateA(aStack, headA);
	// TODO from here down is testing
	t_dlist *tempA = aStack;
	printf("Stack a: \n");
	while (tempA != NULL)
	{
		printf("%s", (char *)tempA->content);
        t_dlist *to_freeA = tempA;
        tempA = tempA->next;
        free (to_freeA);
	}
	t_dlist *tempB = bStack;
	printf("\nStack b: \n");
	while (tempB != NULL)
	{
		printf("%s", (char *)tempB->content);
        t_dlist *to_freeA = tempB;
        tempB = tempB->next;
        free(to_freeA);
	}
}
