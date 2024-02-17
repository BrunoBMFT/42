/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:38:20 by bruno             #+#    #+#             */
/*   Updated: 2024/02/17 04:28:53 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
// REMOVE ALL MALLOCS FROM THIS PART

void	swap(t_ht *lst)
{
	t_dlist	*node1;
	t_dlist	*node2;

	node1 = malloc(sizeof(t_ht));
	node2 = malloc(sizeof(t_ht));
	if (!node1 || !node2)
		return ;
	node1->content = ft_lstrem_front(lst);
	node2->content = ft_lstrem_back(lst);
	ft_lstadd_front(lst, node2);
	ft_lstadd_back(lst, node1);
}

void	push(t_ht *from, t_ht *to)
{
	t_dlist	*node;

	node = malloc(sizeof(t_ht));
	node->content = ft_lstrem_front(from);
	ft_lstadd_front(to, node);
}

void	rotate(t_ht *lst)
{
	t_dlist	*node;

	node = malloc(sizeof(t_ht));
	node->content = ft_lstrem_front(lst);
	ft_lstadd_back(lst, node);
}

void	revrotate(t_ht *lst)
{
	t_dlist	*node;

	node = malloc(sizeof(t_ht));
	node->content = ft_lstrem_back(lst);
	ft_lstadd_front(lst, node);
}
