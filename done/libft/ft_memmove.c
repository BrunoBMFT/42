/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:40:49 by bruno             #+#    #+#             */
/*   Updated: 2023/12/10 18:52:33 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*d;
	char	*s;

	if (dest == src || !n)
		return (dest);
	d = (char *)dest;
	s = (char *)src;
	i = 0;
	if (dest > src)
	{
		while (n-- > 0)
			d[n] = s[n];
	}
	else
	{
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dest);
}
/*#include <stdio.h>
#include <string.h>

int	main(void)
{
	const char src[]  = "newstring";
	char dest[] = "oldstring";
	const char ftsrc[]  = "newstring";
	char ftdest[] = "oldstring";

	printf("Before ft_memmove dest = %s, src = %s\n", ftdest, ftsrc);
	ft_memmove(ftdest, ftsrc, 9);
	printf("After ft_memmove dest = %s, src = %s\n", ftdest, ftsrc);
	printf("Before memmove dest = %s, src = %s\n", dest, src);
	memmove(dest, src, 9);
	printf("After memmove dest = %s, src = %s\n", dest, src);
	
	return(0);
}*/