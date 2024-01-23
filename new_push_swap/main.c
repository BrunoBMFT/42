/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:37:09 by bruno             #+#    #+#             */
/*   Updated: 2024/01/23 01:51:14 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "push_swap.h"

void	newNode(t_dlist *aStack, char *content)
{
	t_dlist *nodetoadd = ft_lstnew(content);
	ft_lstadd_back(&aStack, nodetoadd);
}
void	pushB(t_dlist *aStack, t_dlist **aStackHead, t_dlist *bStack)
{
	bStack->content = aStackHead; // ! head of astack doesnt update
}

int main(int argc, char* argv[])
{
	int	i = 1;
	t_dlist *aStack = NULL;
	t_dlist **aStackHead = &aStack;
	t_dlist *bStack = NULL;
	if (argc >= 2)
	{
		aStack = ft_lstnew(argv[i]);
		bStack = ft_lstnew(NULL);
		i++;
		while (i < argc)
		{
			newNode(aStack, argv[i]);
			i++;
		}
		t_dlist *temp = aStack; // TODO from here down is testing
		while (temp != NULL)
		{
			printf("%s", (char *)temp->content);
            t_dlist *to_free = temp;
            temp = temp->next;
            free(to_free);
			printf("\n\n");
		}
		// ! doesnt work from here on
		printf("hello");
		bStack->content = aStack->content;
		t_dlist *tempo = bStack;
		while (tempo != NULL)
		{
			printf("%s", (char *)tempo->content);
            t_dlist *to_free = tempo;
            tempo = tempo->next;
            free(to_free);
			printf("\n\n");
		}
	}
}
