/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:15:45 by bruno             #+#    #+#             */
/*   Updated: 2024/07/11 03:16:50 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


//env
void	caught_env(char	*input, char **env)
{
	int	i;

	if (ft_strlen(input) > 4)//error and exit code
	{
		printf("minishell env doesnt take that many args\n");
		return ;
	}
	i = 0;
	while (env[i])
	{
		ft_printf("%s\n", env[i]);
		i++;
	}
}
//pwd
void	caught_pwd(char *input, char **env)
{
	int		i;
	char	*pwd;

	if (ft_strlen(input) > 4)//error and exit code
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

//echo
void	caught_echo(t_jobs *job)//fix echo "   hello"
{
	bool	nl;
	
	nl = true;
	if (ft_strnstr(job->cmd, "-n", 7))
		nl = false;
	ft_printf("%s", job->execd);
	if (nl == true)
		ft_nl_fd(1);
}

//cd
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
