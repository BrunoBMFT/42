/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 04:38:12 by bruno             #+#    #+#             */
/*   Updated: 2024/02/19 17:27:59 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void sort3(t_ht *ht_a, t_ht *ht_b)
{
    if (ht_a->head->content > ht_a->head->next->content)
	{
		swap(ht_a);
	}
	ht_b->head = NULL;
}

void	sort(t_ht *ht_a, t_ht *ht_b, int count)
{
	if (count == 4)
		sort3(ht_a, ht_b);
}