/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 22:32:33 by bruno             #+#    #+#             */
/*   Updated: 2023/11/07 14:41:15 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <stdio.h>*/
/*make better and understand*/

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ret;
	int		i;
	int		j;

	if (!s1)
		return (NULL);
	ret = 0;
	if (s1 && set)
	{
		i = 0;
		j = ft_strlen(s1);
		while (s1[i] && ft_strchr(set, s1[i]))
			i++;
		while (s1[j - 1] && ft_strchr(set, s1[j - 1]) && j > i)
			j--;
		ret = (char *)malloc(sizeof(char) * (j - i + 1));
		if (ret == NULL)
			return (NULL);
		if (ret)
			ft_strlcpy(ret, &s1[i], j - i + 1);
	}
	return (ret);
}
/*#include <stdio.h>
int	main(void)
{
	char	*ret;
	char	*str;
	char	*set;

	str = "123hello321";
	set = "123";
	ret = ft_strtrim(str, set);
	printf("%s\n", ret);
	free (ret);
}*/