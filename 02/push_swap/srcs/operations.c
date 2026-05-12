/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:38:20 by bruno             #+#    #+#             */
/*   Updated: 2024/05/08 18:34:16 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

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
		ft_printf("sa\n");
	else if (a_or_b == 'b')
		ft_printf("sb\n");
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
		ft_printf("pa\n");
	else if (a_or_b == 'b')
		ft_printf("pb\n");
}

void	rotate(t_ht *lst, char a_or_b)
{
	t_dlist	*node;

	if (!lst || !lst->head)
		return ;
	node = ft_lstrem_front(lst);
	ft_lstadd_back(lst, node);
	if (a_or_b == 'a')
		ft_printf("ra\n");
	else if (a_or_b == 'b')
		ft_printf("rb\n");
}

void	revrotate(t_ht *lst, char a_or_b)
{
	t_dlist	*node;

	if (!lst || !lst->head)
		return ;
	node = ft_lstrem_back(lst);
	ft_lstadd_front(lst, node);
	if (a_or_b == 'a')
		ft_printf("rra\n");
	else if (a_or_b == 'b')
		ft_printf("rrb\n");
}

void	bothrotate(t_ht *ht_a, t_ht *ht_b)
{
	rotate(ht_a, 'r');
	rotate(ht_b, 'r');
	ft_printf("rr\n");
}
