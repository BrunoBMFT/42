/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:44:53 by bruno             #+#    #+#             */
/*   Updated: 2023/11/07 14:39:43 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	size_t	i;

	if (!str)
		return (NULL);
	i = 0;
	while (i < n)
	{
		*(unsigned char *)(str + i) = (unsigned char)c;
		i++;
	}
	return (str);
}
#include <stdio.h>
#include <string.h>

int main () 
{
	char str[50];

	strcpy(str,"");
	puts(str);

	ft_memset(str,'$',7);
	puts(str);
}