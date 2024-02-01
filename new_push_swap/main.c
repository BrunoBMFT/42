/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:37:09 by bruno             #+#    #+#             */
/*   Updated: 2024/02/01 19:22:51 by brfernan         ###   ########.fr       */
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

/*void	add_top(t_ht *toadd, t_ht *ht) //not working
{
	if (!toadd && !toadd->head)
		return;
	t_dlist *temp = toadd->head; // temp = head of **toadd
	temp->next = ht->head; // next node of temp = head of *ht
	if (ht->head)
		(ht->head)->prev = temp; // if there is a **ht, the previous becomes temp, which is **toadd
	temp->prev = NULL;
	ht->head = temp;
    if (!ht->tail)
        ht->tail = temp;
}

void	remove_top(t_dlist *toremove, t_ht *ht)
{
	
}
void	add_bottom(t_dlist **toadd, t_dlist **tail)
{
	if (!*toadd)
		return;
	t_dlist *temp = *toadd;

	*tail = temp; // makes tail = last value of stack
}*/

void	push(t_ht *from, t_ht *to) // ! WORKING
{
	if (!from || !from->head)
		return;

	t_dlist *temp = from->head; // temp = head of *from
	from->head = temp->next; // head of *from updates to the next node of stack

	if (to)
	{
		temp->next = to->head; // next node of temp = head of *to
		if (to->head)
			to->head->prev = temp; // if there is a *to, the previous becomes temp, which is prev head of *from

		temp->prev = NULL;
		to->head = temp; // makes *to = temp, which is previous head of *from
		if (!to->tail)
			to->tail = temp;
	}
}

void	rotate(t_ht *stack)
{
	if (!stack || !stack->head || !stack->tail)
		return;

	t_dlist *temp = stack->head;
	stack->head = stack->head->next;

	if (stack->head)
		stack->head->prev = NULL;

	temp->prev = stack->tail;
	temp->next = NULL;
	if (stack->tail) 
	{
		stack->tail->next = temp;
	}
	stack->tail = temp;
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
	htA->tail = NULL;
	htB->head = NULL;
	htB->tail = NULL;
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
		while (htA->tail && htA->tail->next) 
    		htA->tail = htA->tail->next;
	}
	
//	push(htA, htB); // pushes htA head to htB head
	rotate(htA);
	// TODO from here down is testing
	t_dlist *tempA = htA->head;
	printf("Stack a: \n");
	while (tempA != NULL)
	{
		printf("%s", (char *)tempA->content);
        t_dlist *to_freeA = tempA;
        tempA = tempA->next;
        free (to_freeA);
	}
	t_dlist *tempB = htB->head;
	printf("\nStack b: \n");
	while (tempB != NULL)
	{
		printf("%s", (char *)tempB->content);
        t_dlist *to_freeA = tempB;
        tempB = tempB->next;
        free(to_freeA);
	}
	free (htA);
	free (htB);
}
