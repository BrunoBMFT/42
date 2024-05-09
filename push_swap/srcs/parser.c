/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 23:31:04 by bruno             #+#    #+#             */
/*   Updated: 2024/05/08 18:34:17 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	initiate(t_ht *ht_a, t_ht *ht_b)
{
	ht_a->head = NULL;
	ht_a->tail = NULL;
	ht_b->head = NULL;
	ht_b->tail = NULL;
	ht_a->size = 0;
	ht_b->size = 0;
}

bool	parse_digit(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9') || str[i] == '-')
			return (false);
		i++;
	}
	return (true);
}

bool	parse_doubles(char **str, int content, t_ht *stack)
{
	t_dlist	*temp;
	int		i;

	i = 0;
	temp = stack->head;
	while (str[i])
	{
		while (temp)
		{
			if (temp->value == content)
				return (false);
			temp = temp->next;
		}
		i++;
	}
	return (true);
}

bool	parser(int ac, char **av, t_ht *ht_a)
{
	int		i;

	i = 1;
	if (ac <= 2)
		return (0);
	else if (ac >= 3)
	{
		while (i < ac)
		{
			if (ac <= 2)
				return (0);
			if (!parse_digit(av[i])
				|| !parse_doubles(av, ft_atol(av[i]), ht_a)
				|| ft_atol(av[i]) > INT_MAX || ft_atol(av[i]) < INT_MIN)
				return (ft_lstclear(ht_a), ft_printf("Error\n"), false);
			new_node(ht_a, ft_atol(av[i]));
			i++;
		}
	}
	return (true);
}
