/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 02:41:58 by bruno             #+#    #+#             */
/*   Updated: 2024/02/17 04:29:05 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>

typedef struct s_dlist
{
	int				content;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}					t_dlist;

typedef struct s_ht
{
	t_dlist	*head;
	t_dlist	*tail;
}					t_ht;

t_dlist	*ft_lstnew(int content);
void	new_node(t_ht *lst, int content);
void	ft_lstadd_front(t_ht *lst, t_dlist *new);
void	ft_lstadd_back(t_ht *lst, t_dlist *new);
int		ft_lstrem_front(t_ht *lst);
int		ft_lstrem_back(t_ht *lst);
void	ft_lstdelone(t_dlist *lst);
void	ft_lstclear(t_dlist **lst);
void	lst_print(t_ht *lst);
//operations
void	push(t_ht *from, t_ht *to);
void	rotate(t_ht *lst);
void	revrotate(t_ht *lst);
void	swap(t_ht *lst);
//libft
size_t	ft_strlen(const char *str);
char	**ft_split(char const *s, char c);
long	ft_atol(const char *str);

#endif