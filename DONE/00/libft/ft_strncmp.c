/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:39:34 by brfernan          #+#    #+#             */
/*   Updated: 2023/12/10 18:53:06 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] && s1[i] == s2[i])
	{
		if (i < (n - 1))
			i++;
		else
			return (0);
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
/*#include <stdio.h>
#include <string.h>
int main () 
{
   char str1[15];
   char str2[15];
   int ftret;
   int ret;

   strcpy(str1, "test");
   strcpy(str2, "test");

   ftret = ft_strncmp(str1, str2, 7);
   printf("%d\n", ftret);
   ret = strncmp(str1, str2, 7);
   printf("%d\n", ret);
}*/