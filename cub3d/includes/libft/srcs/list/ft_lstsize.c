/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:25:33 by brfernan          #+#    #+#             */
/*   Updated: 2024/12/16 04:08:25 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

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
