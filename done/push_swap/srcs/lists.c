/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:57:40 by bruno             #+#    #+#             */
/*   Updated: 2024/05/08 18:33:52 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

t_dlist	*ft_lstnew(int value)
{
	t_dlist	*current;

	current = malloc(sizeof(t_dlist));
	if (!current)
		return (NULL);
	current->value = value;
	current->next = NULL;
	current->prev = NULL;
	return (current);
}

void	new_node(t_ht *lst, int value)
{
	t_dlist	*toadd;

	lst->size++;
	toadd = ft_lstnew(value);
	ft_lstadd_back(lst, toadd);
}

void	ft_lstclear(t_ht *stack)
{
	t_dlist	*temp;

	if (!stack)
		return ;
	while (stack->head)
	{
		temp = stack->head->next;
		free(stack->head);
		stack->head = temp;
	}
	stack->head = NULL;
	stack->tail = NULL;
}

void	normalizer_aux(t_dlist *t1, t_dlist *t2, t_ht *lst, int count)
{
	while (t1)
	{
		count = 1;
		t2 = lst->head->next;
		while (t1 && t2)
		{
			if (t2->value < t1->value)
				count++;
			t2 = t2->next;
		}
		t1->value = count;
		t1 = t1->next;
	}
}

void	normalizer(t_dlist *head_a)
{
	t_dlist	*t1;
	t_dlist	*t2;
	t_ht	lst;
	int		count;

	t1 = head_a;
	lst.tail = NULL;
	lst.head = head_a;
	count = 1;
	while (t1)
	{
		new_node(&lst, t1->value);
		t1 = t1->next;
	}
	t1 = lst.head;
	t2 = lst.head->next;
	normalizer_aux(t1, t2, &lst, count);
	ft_lstclear(&lst);
}
