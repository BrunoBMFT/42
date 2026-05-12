/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:19:13 by brfernan          #+#    #+#             */
/*   Updated: 2024/12/16 04:07:26 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	i = 0;
	j = 0;
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

char	*ft_strjoin3(char const *s1, char const *s2, char const *s3)
{
	int		i;
	int		j;
	int		k;
	char	*full;

	i = -1;
	j = 0;
	k = 0;
	full = ft_calloc((ft_strlen(s1)
				+ ft_strlen(s2) + ft_strlen(s3)) + 1, sizeof(char));
	if (full == NULL)
		return (NULL);
	while (s1 && s1[++i])
		full[i] = s1[i];
	while (s2 && s2[j])
		full[i++] = s2[j++];
	while (s3 && s3[k])
		full[i++] = s3[k++];
	full[i] = '\0';
	return (full);
}
