/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:37:09 by bruno             #+#    #+#             */
/*   Updated: 2024/01/27 13:16:03 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "push_swap.h"

void	new_node(t_dlist *aStack, char *content)
{
	t_dlist *toadd = ft_lstnew(content);
	ft_lstadd_back(&aStack, toadd);
}
// ! MUDAR PARA ADDTOP, ADDBOTTOM, REMOVETOP, REMOVEBOTTOM
// ! funciona na mesma para push e rotate
// ? rotate a é removeTop e addBottom
// ? reverse rotate é removeBottom e addTop
// ? push é removeTopA e addTopB ou vice versa (fazer com que função nao precise do a, tipo a push ja feita)
/*void	add_top(t_dlist **toadd, t_ht *ht)
{
	if (!*toadd)
		return;
	t_dlist *temp = *toadd; // temp = head of **toadd
	temp->next = ht->head; // next node of temp = head of *ht
	if (ht->head)
		(ht->head)->prev = temp; // if there is a **ht, the previous becomes temp, which is **toadd
	temp->prev = NULL;
	ht->head = temp;
    if (!ht->tail)
        ht->tail = temp;
}

void	add_bottom(t_dlist **toadd, t_dlist **tail)
{
	if (!*toadd)
		return;
	t_dlist *temp = *toadd;

	*tail = temp; // makes tail = last value of stack
}*/

void	push(t_ht **from, t_ht **to)
{
	if (!*from)
		return;
	t_dlist *temp = (*from)->head; // temp = head of **from
	(*from)->head = temp->next; // head of **from updates to the next node of stack
	
	temp->next = (*to)->head; // next node of temp = head of **to
	if (*to && (*to)->head) 
		(*to)->head->prev = temp; // if there is a **to, the previous becomes temp, which is prev head of **from
	
	temp->prev = NULL;
	(*to)->head = temp; // makes **to = temp, which is previous head of **from
	if (!(*to)->tail)
		(*to)->tail = temp;
}

int main(int argc, char* argv[])
{
	int	i = 1;
	// * NORM, instead of aStack, something like a_stack
	t_dlist *aStack = NULL;
	t_ht 	*htA = malloc(sizeof(t_ht));
	t_dlist *bStack = NULL;
	t_ht 	*htB = malloc(sizeof(t_ht));
	
	htA->head = NULL;
	htB->head = bStack;
	if (argc >= 2)
	{
		aStack = ft_lstnew(argv[i]);
		htA->head = aStack;
		i++;
		while (i < argc)
		{
			new_node(aStack, argv[i]);
			i++;
		}
	}
//	t_dlist *node1 = malloc(sizeof(t_dlist));
//	node1->content = "hi";
	push(&htA, &htB);
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
		printf("debug\n");
		printf("%s", (char *)tempB->content);
        t_dlist *to_freeA = tempB;
        tempB = tempB->next;
        free(to_freeA);
	}
	free (htA);
	free (htB);
}
