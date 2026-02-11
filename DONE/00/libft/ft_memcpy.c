/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:34:43 by bruno             #+#    #+#             */
/*   Updated: 2023/12/10 18:52:06 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*d;
	char	*s;

	if (dest == src || !n)
		return (dest);
	i = 0;
	d = (char *)dest;
	s = (char *)src;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}
/*#include <stdio.h>
#include <string.h>

int	main () 
{
	const char ft_src[50] = "hi";
	char ft_dest[50];
	const char src[50] = "hi";
	char dest[50];
	strcpy(ft_dest, "hello");
	printf("Before ft_memcpy dest = %s\n", ft_dest);
	ft_memcpy(ft_dest, ft_src, ft_strlen(ft_src)+1);
	printf("After ft_memcpy dest = %s\n", ft_dest);
	strcpy(dest, "hello");
	printf("Before memcpy dest = %s\n", dest);
	memcpy(dest, src, ft_strlen(src)+1);
	printf("After memcpy dest = %s\n", dest);
}*/
