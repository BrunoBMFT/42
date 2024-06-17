/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 21:30:07 by bruno             #+#    #+#             */
/*   Updated: 2024/06/17 21:55:16 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	caught_exit_status()
{
	ft_putendl_fd("nice exit code expanded here", 1);//stdout?
}

int	caught_env_variable(char *env_var, char **envp)
{
	int		i = 0;
	char	*trimmed;
	char	*temp;
	char	*to_write;

	env_var = ft_strtrim(env_var, "$");
	if (env_var[0] == '?')
		return (caught_exit_status, 0);
	while (ft_strnstr(envp[i], env_var, ft_strlen(env_var)) == 0)
	{
		if (i > 23)
			return (ft_nl_fd(1), 0);//0 because error code of no env var is 0
		i++;
	}
	to_write = ft_strtrim(envp[i], env_var);
	if (to_write[0] == '=')
	{
		to_write = ft_strtrim(to_write, "=");
		ft_putendl(to_write);
	}
	return (1);
}
