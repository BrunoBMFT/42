/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:37:09 by bruno             #+#    #+#             */
/*   Updated: 2024/04/06 16:54:30 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "push_swap.h"

// TODO for functions sending lists, send only the pointer to head
// *change ht_a name

int	main(int ac, char **av)
{
	t_ht	ht_a;
	t_ht	ht_b;

	initiate(&ht_a, &ht_b);
	if (!parser(ac, av, &ht_a))
		return (1);
	sort(&ht_a, &ht_b);
}
