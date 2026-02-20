/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:01:46 by bruno             #+#    #+#             */
/*   Updated: 2023/12/10 18:49:47 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*p;

	i = 0;
	p = (char *)s;
	while (i < n)
	{
		if ((unsigned char)p[i] == (unsigned char)c)
			return ((char *)p + i);
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	char	str[] = "hello";
	char	c = 'e';
	char	*ft_ret;
	char	*ret;

	ft_ret = ft_memchr(str, c, 5);
	printf("%s\n", ft_ret);
	ret = memchr(str, c, 5);
	printf("%s\n", ret);
}*/
