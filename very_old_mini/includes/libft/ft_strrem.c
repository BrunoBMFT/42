/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:25:08 by bruno             #+#    #+#             */
/*   Updated: 2024/07/01 15:51:37 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrem(char *str, char *to_remove)
{
	int		i;
	int		j;
	char	*new;

	if (!*str || !*to_remove)
		return (NULL);
	i = 0;
	j = 0;
	new = malloc(sizeof(char) * (ft_strlen(str) - ft_strlen(to_remove) + 1));
	if (!new)
		return (NULL);
	while (str[i])
	{
		if (ft_strncmp(&str[i], to_remove, ft_strlen(to_remove)) == 0)
			i += ft_strlen(to_remove);
		else
			new[j++] = str[i++];
	}
	new[j] = 0;
	return (new);
}
