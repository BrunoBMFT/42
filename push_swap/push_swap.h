/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 02:41:58 by bruno             #+#    #+#             */
/*   Updated: 2024/03/07 16:59:39 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdio.h>//remove
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>

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
	int		cost;
	int		bff;
}					t_ht;

t_dlist	*ft_lstnew(int content);
void	new_node(t_ht *lst, int content);
void	ft_lstadd_front(t_ht *lst, t_dlist *new);
void	ft_lstadd_back(t_ht *lst, t_dlist *new);
t_dlist	*ft_lstrem_front(t_ht *lst);
t_dlist	*ft_lstrem_back(t_ht *lst);
void	ft_lstdelone(t_dlist *lst);
void	lst_print(t_ht *lst);
void	ft_lstclear(t_ht *ht_a);
//operations
void	push(t_ht *from, t_ht *to, char a_or_b);
void	rotate(t_ht *lst, char a_or_b);
void	revrotate(t_ht *lst, char a_or_b);
void	swap(t_ht *lst, char a_or_b);
//sort
int		is_sorted(t_ht *ht_a);
void	sort(t_ht *ht_a, t_ht *ht_b, int count);
void	sort3(t_ht *ht_a);
void	something_sort(t_ht ht_a, t_ht ht_b);
int		bestfriend(t_ht ht_a, t_dlist *node_b);

//cost
int		cost_calc(t_ht ht_a, t_ht ht_b, t_dlist *node);
int		cost_head(t_ht ht_a, t_ht ht_b, t_dlist *node);

//libft
size_t	ft_strlen(const char *str);
char	**ft_split(char const *s, char c);
long	ft_atol(const char *str);
int		ft_isdigit(int c);
int		ft_putstr(char *s);
void	ft_free_all(char **tofree);

#endif