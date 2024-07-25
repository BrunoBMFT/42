/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 18:16:48 by bruno             #+#    #+#             */
/*   Updated: 2024/07/24 20:53:00 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	len_to_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

char	*ft_env_var(char *str)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '=')
		i++;
	i++;
	new = ft_calloc(sizeof(char), (ft_strlen(str) - len_to_equal(str)));
	if (!new)
		return (NULL);
	while (str[i])
	{
		new[j] = str[i];
		j++;
		i++;
	}
	new[j] = 0;
	return (new);
}

char	*ft_getenv(char *str, char **env)
{
	char	*temp;
	int		i;

	if (!str || !*str || !env || !*env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		temp = ft_strndup(env[i], len_to_equal(env[i]));
		if (!temp)
			return (NULL);
		if (ft_strncmp(str, temp, ft_strlen(temp) + 1) == 0)
			return (free (temp), ft_env_var(env[i]));
		free (temp);
		i++;
	}
	return (NULL);
}
