/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 20:13:16 by bruno             #+#    #+#             */
/*   Updated: 2024/07/02 01:01:39 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
// ! ERROR CHECK EVERY MALLOC FUNCTION
// * change everything to fd functions
// TODO check return codes for getcwd, chdir, readline
// TODO make a function to find env variables (less use of strnstr(env, env_var))
void	update_pwd(char **env, bool when)
{
	char	cwd[100];
	char	*temp;

	int	i = 0;
	if (when == BEFORE)
	{
		while (ft_strnstr(env[i], "OLDPWD", 6) == 0 && i < 31)//2nd condition so no segfaults
			i++;
		temp = getcwd(cwd, sizeof(cwd));
		env[i] = ft_strjoin("OLDPWD=", temp);
	}
	else
	{
		while (ft_strnstr(env[i], "PWD", 3) == 0 && i < 31)//2nd condition so no segfaults
			i++;
		temp = getcwd(cwd, sizeof(cwd));
		env[i] = ft_strjoin("PWD=", temp);
	}
	
}

void	cd_home(char **env)
{
	int		i;
	char	*directory;

	i = 0;
	while (ft_strnstr(env[i], "HOME", 4) == 0)
		i++;
	directory = ft_strrem(env[i], "HOME=");
	chdir(directory);
}

void	caught_cd(char *input, char **env)
{
	char 	*directory;
	
	update_pwd(env, BEFORE);
	directory = ft_strrem(input, "cd");
	if (!*directory)
		cd_home(env);
	else
		directory = ft_strrem(directory, " ");// ! dont hard code like this
	chdir(directory);
	update_pwd(env, AFTER);
}

void	caught_env(char **env)
{
	int	i, j;

	i = 0;
	while (env[i])
	{
		ft_putendl(env[i]);
		i++;
	}		
}

void	caught_pwd(char **env)
{
	int		i;

	i = 0;
	while (ft_strnstr(env[i], "PWD", 3) == 0)
		i++;
	ft_printf("%s\n", ft_strrem(env[i], "PWD="));
}

void	expand_input(char *input, char **env)
{
//	ft_printf("%s\n", input);
	
	input = expand_env_vars(input, env);
	if (!input)
		return ;
	if (ft_strnstr(input, "echo", 4))
		caught_echo(input);
	if (ft_strnstr(input, "cd", 4))
		caught_cd(input, env);
	if (ft_strnstr(input, "env", 3))
		caught_env(env);
	if (ft_strnstr(input, "pwd", 3))
		caught_pwd(env);

//	ft_printf("expanded:\n%s", input);//expander test
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	char	*prompt;
	char	**env;

	env = envp;
	while (1)
	{
		prompt = update_prompt();
		input = readline(prompt);
		if (input)
			expand_input(input, env);
		if (ft_strnstr(input, "exit", 4))
			return (rl_clear_history(), free(input), exit(0), 0);
//		ft_nl_fd(1);
	}
}