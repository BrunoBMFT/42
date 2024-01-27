/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 02:41:58 by bruno             #+#    #+#             */
/*   Updated: 2024/01/16 19:11:01 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_dlist
{
	void			*content;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}					t_dlist;

t_dlist	*ft_lstnew(void *content);
t_dlist	*ft_lstlast(t_dlist *lst);
void	ft_lstadd_front(t_dlist **lst, t_dlist *new);
void	ft_lstadd_back(t_dlist **lst, t_dlist *new);
void	ft_lstdelone(t_dlist *lst);
void	ft_lstclear(t_dlist **lst);

#endif