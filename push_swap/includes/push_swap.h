/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 02:41:58 by bruno             #+#    #+#             */
/*   Updated: 2024/04/22 17:02:45 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include "libft/libft.h"

typedef struct s_dlist
{
	int				value;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}					t_dlist;

typedef struct s_ht
{
	t_dlist	*head;
	t_dlist	*tail;
	int		bff;
	int		size;
	int		smallest;
	int		median;
}					t_ht;

typedef struct s_cost
{
	bool	direction_a;
	bool	direction_b;
	int		cost;
	int		b_node;
	int		a_node;
}				t_cost;

//parsing
bool	parser(int ac, char **av, t_ht *ht_a);
void	normalizer(t_dlist *head_a);
//lists
void	initiate(t_ht *ht_a, t_ht *ht_b);
void	new_node(t_ht *lst, int content);
void	ft_lstadd_front(t_ht *lst, t_dlist *new);
void	ft_lstadd_back(t_ht *lst, t_dlist *new);
t_dlist	*ft_lstrem_front(t_ht *lst);
t_dlist	*ft_lstrem_back(t_ht *lst);
void	ft_lstclear(t_ht *stack);
//operations
void	push(t_ht *from, t_ht *to, char a_or_b);
void	rotate(t_ht *lst, char a_or_b);
void	revrotate(t_ht *lst, char a_or_b);
void	swap(t_ht *lst, char a_or_b);
void	bothrotate(t_ht *ht_a, t_ht *ht_b);
void	bothrevrotate(t_ht *ht_a, t_ht *ht_b);
//sort
void	sort(t_ht *ht_a, t_ht *ht_b);
void	sort3(t_ht *ht_a);
void	sort_bestfriend(t_ht ht_a, t_ht ht_b);
int		find_small(t_ht *stack);
int		find_median(t_dlist *head_a);
void	push_to_b(t_ht *ht_a, t_ht *ht_b);
void	prep_push(t_ht *ht_a, t_ht *ht_b, t_cost min);
void	rotate_to_first(t_ht *ht_a);
//cost
int		cost_head_a(t_dlist *a_node, int bff);
int		cost_head_b(t_dlist *b_node, t_dlist *node);
int		cost_tail_a(t_dlist *a_node, int bff);
int		cost_tail_b(t_dlist *b_node, t_dlist *node);
//libft
long	ft_atol(const char *str);
int		ft_printf(const char *str, ...);
int		ft_putstr(char *str);

#endif