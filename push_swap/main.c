/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 02:41:43 by bruno             #+#    #+#             */
/*   Updated: 2023/11/28 16:35:52 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_dlist *list = NULL;
	t_pointer ht;
	ht.head = NULL;
	ht.tail = NULL;
	int	sorted = 0; //define as bool
	int	i;

	i = 1;
	if (argc == 2)
	{
		char	**arr = ft_split(argv[i], ' ');
		sorted = is_sorted(arr);
	}
	if (argc >= 2)
	{
		list = lstnew(argv[1]);
		if (!list)
			return (1);
		while (argv[i])
		{
			lstadd_back(&ht, list);
			i++;
			list = list->next;
		}
		while (i > 0)
		{
			printf("%s\n", (char *)list->content);
			list = list->next;
		}
	}
	lstclear(&ht);
	return (0);
}
