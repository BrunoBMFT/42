/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 19:27:04 by brfernan          #+#    #+#             */
/*   Updated: 2023/12/10 18:52:45 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return ((char *)(str + i));
		i++;
	}
	if (str[i] == (char)c)
		return ((char *)(str + i));
	return (0);
}
/*#include <stdio.h>
int main ()
{
	const char str[] = "";
	int ch = 's';
	char *ret;

	ret = ft_strchr(str, ch);

	printf("String after %c is - %s\n", ch, ret);

	return(0);
}*/
