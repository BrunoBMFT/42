/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:25:08 by bruno             #+#    #+#             */
/*   Updated: 2024/06/29 23:05:05 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrem(char *str, char *to_remove)//
{
	int		i;
	int		count;
	char	*new;

	new = NULL;
	i = 0;
	while (*str)
	{
		if (ft_strncmp(str, to_remove, ft_strlen(to_remove)) == 0)
			break;
		count++;
		str++;
	}
	new = malloc(sizeof(char) * count);
	if (!new)
		return (NULL);
	while (to_remove[i])
	{
		new[i] = *str;
		i++;
		str++;
	}
	return (new);
}