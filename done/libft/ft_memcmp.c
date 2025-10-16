/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:22:18 by bruno             #+#    #+#             */
/*   Updated: 2023/12/10 18:53:12 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}
/*#include <stdio.h>
#include <string.h>
int	main(void)
{  
	char str1[15];
	char str2[15];
	int ret;
	int ft_ret;

	ft_ret = ft_memcmp("t\200", "t\0", 2);
	if(ft_ret > 0) {
		printf("str2 is less than str1\n");
	} else if(ft_ret < 0) {
		printf("str1 is less than str2\n");
	} else {
		printf("str1 is equal to str2\n");
	}
	
	ret = memcmp("t\200", "t\0", 2);
	if(ret > 0) {
		printf("str2 is less than str1\n");
	} else if(ret < 0) {
		printf("str1 is less than str2\n");
	} else {
		printf("str1 is equal to str2\n");
	}
}*/