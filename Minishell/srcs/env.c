/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 19:25:47 by bruno             #+#    #+#             */
/*   Updated: 2024/07/07 20:32:52 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	caught_env(char	*input, char **env)
{
	int	i;

	if (ft_strlen(input) > 4)
	{
		printf("minishell env doesnt take that many args\n");
		return ;
	}
	i = 0;
	while (env[i])
	{
		ft_putnbr(i);
		ft_putstr(": ");
		ft_putendl(env[i]);
		i++;
	}
}

void	caught_pwd(char *input, char **env)
{
	int		i;
	char	*pwd;

	if (ft_strlen(input) > 4)
	{
		printf("minishell env doesnt take that many args\n");
		return ;
	}
	i = 0;
	while (ft_strnstr(env[i], "PWD", 3) == 0)
		i++;
	pwd = ft_strrem(env[i], "PWD=");
	ft_printf("%s\n", pwd);
	free (pwd);
}
