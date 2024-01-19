/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:37:09 by bruno             #+#    #+#             */
/*   Updated: 2024/01/19 16:38:58 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "push_swap.h"

void	newNode(t_dlist *aStack, char *content)
{
	t_dlist *nodetoadd = ft_lstnew(content);
	ft_lstadd_back(&aStack, nodetoadd);
}

int main(int argc, char* argv[])
{
	int	i = 1;
	t_dlist *aStack = NULL; // change to double pointer according to daan
	if (argc >= 2)
	{
		aStack = ft_lstnew(argv[i]);
		i++;
		while (i < argc)
		{
			newNode(aStack, argv[i]);
			i++;
		}
		t_dlist *temp = aStack; //from here down is testing
		while (temp != NULL)
		{
			printf("%s", (char *)temp->content);
            t_dlist *to_free = temp;
            temp = temp->next;
            free(to_free);
		}
	}
}
