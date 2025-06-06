/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 19:38:57 by brfernan          #+#    #+#             */
/*   Updated: 2024/12/16 04:07:26 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_strnstr(const char *str, const char *little, size_t n)
{
	size_t	pos;

	if (!str)
		return (NULL);
	if (!*little)
		return ((char *)str);
	pos = ft_strlen((char *)little);
	while (*str && n-- >= pos)
	{
		if (*str == *little && ft_memcmp(str, little, pos) == 0)
			return ((char *)str);
		str++;
	}
	return (NULL);
}
