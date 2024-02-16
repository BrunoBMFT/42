/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:38:20 by bruno             #+#    #+#             */
/*   Updated: 2024/02/16 16:38:46 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push(t_ht *from, t_ht *to)
{
	t_dlist *node = malloc(sizeof(t_ht)); //remove malloc
	node->content = ft_lstrem_front(from);
	ft_lstadd_front(to, node);
}

void	rotate(t_ht *lst)
{
	t_dlist	*node = malloc(sizeof(t_ht)); // remove malloc
	node->content = ft_lstrem_front(lst);
	ft_lstadd_back(lst, node);
}

void	revrotate(t_ht *lst)
{
	t_dlist	*node = malloc(sizeof(t_ht)); // remove malloc
	node->content = ft_lstrem_back(lst);
	ft_lstadd_front(lst, node);
}