/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:25:33 by bruno             #+#    #+#             */
/*   Updated: 2023/10/24 17:52:10 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	n;

	n = 0;
	while (lst)
	{
		lst = lst->next;
		n++;
	}
	return (n);
}
/*#include <stdio.h>
int	main(void)
{
	t_list *lst = malloc(sizeof(t_list));
	lst->content = "hi";
	lst->next = (t_list *)malloc(sizeof(t_list));
	lst->next->content = "hello";
	lst->next->next = NULL;
	int ret = ft_lstsize(lst);
	printf("%d\n", ret);
}*/
