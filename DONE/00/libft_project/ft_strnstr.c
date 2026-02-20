/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 19:38:57 by brfernan          #+#    #+#             */
/*   Updated: 2023/12/10 18:49:13 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *little, size_t n)
{
	size_t	pos;

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
/*#include <stdio.h>
int	main(void)
{
	char	*big = "hello world";
	char	*little = "wo";
	char	*ftptr;
	char	*ptr;
	ftptr = ft_strnstr(big, little, 10);
	printf("%s\n", ftptr);
}*/
