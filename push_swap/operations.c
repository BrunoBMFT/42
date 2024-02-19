/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:38:20 by bruno             #+#    #+#             */
/*   Updated: 2024/02/19 23:10:02 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap(t_ht *lst)// first two swap (t_ht *lst, char a_or_b)
{
	t_dlist	*node1;
	t_dlist	*node2;

	if (!lst)
		return ;
	node1 = ft_lstrem_front(lst);
	node2 = ft_lstrem_front(lst);
	ft_lstadd_front(lst, node1);
	ft_lstadd_front(lst, node2);
	/*if (a_or_b == a)
		printf("sa");
	else
		printf("sb");*/
}



void	push(t_ht *from, t_ht *to)// stack to stack
{
	t_dlist	*node;

	if (!from || !to)
		return ;
	node = ft_lstrem_front(from);
	ft_lstadd_front(to, node);
}

void	rotate(t_ht *lst)// front to back
{
	t_dlist	*node;

	if (!lst)
		return ;
	node = ft_lstrem_front(lst);
	ft_lstadd_back(lst, node);
}

void	revrotate(t_ht *lst)// back to front
{
	t_dlist	*node;

	if (!lst)
		return ;
	node = ft_lstrem_back(lst);
	ft_lstadd_front(lst, node);
}
