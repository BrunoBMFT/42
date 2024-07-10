/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:15:45 by bruno             #+#    #+#             */
/*   Updated: 2024/07/10 17:04:09 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	update_pwd(char **env, bool when)
{
	char	cwd[100];
	char	*temp;

	int	i = 0;
	if (when == BEFORE)
	{
		while (env[i] && ft_strnstr(env[i], "OLDPWD", 6) == 0)//fix oldpwd when cd fails
			i++;
		temp = getcwd(cwd, sizeof(cwd));//error check
		env[i] = ft_strjoin("OLDPWD=", temp);//error check
	}
	else
	{
		while (env[i] && ft_strnstr(env[i], "PWD", 3) == 0)
			i++;
		temp = getcwd(cwd, sizeof(cwd));//error check
		env[i] = ft_strjoin("PWD=", temp);//error check
	}
}

void	caught_cd(t_jobs *job, char **env)// * if trying to cd to home, will job just be "cd"?
{
	char 	*directory;
	
	update_pwd(env, BEFORE);
	directory = job->execd;
//	directory = ft_strrem(input, "cd");//problem: "cd DIR"
	if (!*directory)
	{
		if (chdir(getenv("HOME")) < 0)//error and exit code, dont use getenv
			return (printf("cd home failed\n"), (void)NULL);// * need to fix perror
		else
			return ;
	}
	if (chdir(directory) < 0)
		return (printf("cd failed\n"), (void)NULL);// * need to fix perror
	update_pwd(env, AFTER);
}
