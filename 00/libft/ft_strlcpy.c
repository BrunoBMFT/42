/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 19:43:47 by brfernan          #+#    #+#             */
/*   Updated: 2023/12/10 18:49:18 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
	{
		while (src[i])
			i++;
		return (i);
	}
	while (src[i] && i < (n - 1))
	{
		dst[i] = src[i];
		i++;
	}
	if (i < n)
		dst[i] = '\0';
	while (src[i])
		i++;
	return (i);
}
/*#include <stdio.h>
#include <string.h>
int	main(void)
{
    char src[] = "Hello there";
    char ftdest[19];
    char dest[19];
    int r;
    int ftr;

    ftr = ft_strlcpy(ftdest, src, 10);
    r = ft_strlcpy(ftdest, src, 10);
    printf("%d\n", ftr);
    printf("%d\n", r);
}*/
