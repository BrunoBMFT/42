/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 02:41:58 by bruno             #+#    #+#             */
/*   Updated: 2024/03/24 17:29:40 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
//take useless functions from header (functions not used on other files)
# include <stdio.h>//remove
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>

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
	bool 	direction_a;
	bool 	direction_b;
	bool	no_bff;//1 if no bff found
	int		to_sort;
	int		cost;
	int		b_node;
	int		a_node;
}				t_cost;

//parsing
int	parse_digit(char *str);
int	parse_doubles(char **str, int content, t_ht *stack);
void	normalizer(t_ht *stack);
//lists
void	initiate(t_ht *ht_a, t_ht *ht_b);
t_dlist	*ft_lstnew(int content);
void	new_node(t_ht *lst, int content);
void	ft_lstadd_front(t_ht *lst, t_dlist *new);
void	ft_lstadd_back(t_ht *lst, t_dlist *new);
t_dlist	*ft_lstrem_front(t_ht *lst);
t_dlist	*ft_lstrem_back(t_ht *lst);
void	ft_lstdelone(t_dlist *lst);
void	lst_print(t_ht *lst, char a_or_b);
void	ft_lstclear(t_ht *ht_a);

//operations
void	push(t_ht *from, t_ht *to, char a_or_b);
void	rotate(t_ht *lst, char a_or_b);
void	revrotate(t_ht *lst, char a_or_b);
void	swap(t_ht *lst, char a_or_b);
void	bothrotate(t_ht ht_a, t_ht ht_b);
void	bothrevrotate(t_ht ht_a, t_ht ht_b);

//sort
int		is_sorted(t_ht *ht_a);
void	sort(t_ht *ht_a, t_ht *ht_b, int count);
void	sort3(t_ht *ht_a);
void 	sort_bestfriend(t_ht ht_a, t_ht ht_b);
int		bestfriend(t_ht ht_a, t_dlist *node_b);
int		find_small(t_ht *ht_a);
bool	is_biggest(t_ht *stack);
//void 	sort_list(t_dlist *head);
//int 	find_median(t_ht *stack);


//cost
t_cost	cost_calc(t_ht *ht_a, t_ht *ht_b, int bff, t_dlist *node);
int		cost_head_a(t_ht ht_a, int bff);
int		cost_head_b(t_ht ht_b, t_dlist *node);
int		cost_tail_a(t_ht ht_a, int bff);
int		cost_tail_b(t_ht ht_b, t_dlist *node);
t_cost	minimum_cost(t_ht ht_a, t_ht ht_b);

//libft
long	ft_atol(const char *str);
int		ft_isdigit(int c);
int		ft_putstr(char *s);

#endif