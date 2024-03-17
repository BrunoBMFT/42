/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:38:20 by bruno             #+#    #+#             */
/*   Updated: 2024/03/16 23:28:03 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
swap: first two swap (t_ht *lst, char a_or_b)
push: from stack to stack
rot:  front to back
rrot: back to front
*/
void	swap(t_ht *lst, char a_or_b)
{
	t_dlist	*node1;
	t_dlist	*node2;

	if (!lst || !lst->head)
		return ;
	node1 = ft_lstrem_front(lst);
	node2 = ft_lstrem_front(lst);
	ft_lstadd_front(lst, node1);
	ft_lstadd_front(lst, node2);
	if (a_or_b == 'a')
		ft_putstr("sa");
	else if (a_or_b == 'b')
		ft_putstr("sb");
}

void	push(t_ht *from, t_ht *to, char a_or_b)
{
	t_dlist	*node;

	if (!from || !to || !from->head)
		return ;
	node = ft_lstrem_front(from);
	ft_lstadd_front(to, node);
	from->size--;
	to->size++;
	if (a_or_b == 'a')
		ft_putstr("pa");
	else if (a_or_b == 'b')
		ft_putstr("pb");
}

void	rotate(t_ht *lst, char a_or_b)
{
	t_dlist	*node;

	if (!lst || !lst->head)
		return ;
	node = ft_lstrem_front(lst);
	ft_lstadd_back(lst, node);
	if (a_or_b == 'a')
		ft_putstr("ra");
	else if (a_or_b == 'b')
		ft_putstr("rb");
}

void	revrotate(t_ht *lst, char a_or_b)
{
	t_dlist	*node;

	if (!lst || !lst->head)
		return ;
	node = ft_lstrem_back(lst);
	ft_lstadd_front(lst, node);
	if (a_or_b == 'a')
		ft_putstr("rra");
	else if (a_or_b == 'b')
		ft_putstr("rrb");
}

