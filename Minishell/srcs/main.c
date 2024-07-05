/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 20:13:16 by bruno             #+#    #+#             */
/*   Updated: 2024/07/05 17:49:04 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
// redirections for all builtins, have them prepared
// * exit codes
// * ERROR CHECK EVERY MALLOC FUNCTION
// * change everything to fd functions
// TODO check return codes for getcwd, chdir, readline
// TODO make a function to find env variables (less use of strnstr(env, env_var))
// * parse things like envfffdff or pwde
// ? start using strcmp instead of strnstr
void	caught_unset(char *input, char **env)
{
	int		i;
	int		j;
	char	*to_remove;
	char	*var;
	char	**new_env;

	var = ft_strrem(input, "unset ");
	new_env = ft_calloc(sizeof(char *), ft_split_wordcount(env) - 1);
	i = 0;
	while (env[i] && ft_strnstr(env[i], var, ft_strlen(var)) == 0)
		i++;
	if (!env[i])
		return ((void)NULL);
	to_remove = env[i];
	i = 0;
	j = 0;
	while (env[i])//move with pointer
	{
		if (ft_strnstr(env[i], to_remove, ft_strlen(to_remove)) == 0)
		{
			new_env[j] = env[i];
			j++;
		}
		else
		{
			i++;
		}
	}
	env = new_env;
}

void	expand_input(char *input, char **env)
{
	input = expand_env_vars(input, env);
	if (!input)
		return ;
	else if (ft_strnstr(input, "cd", 2))
		caught_cd(input, env);
	else if (ft_strnstr(input, "echo", 4))
		caught_echo(input);
	else if (ft_strnstr(input, "env", 3))
		caught_env(input, env);
	else if (ft_strnstr(input, "pwd", 3))
		caught_pwd(input, env);
	else if (ft_strnstr(input, "unset", 5))
		caught_unset(input, env);
//	else if (ft_strnstr(input, "export", 6))
//		caught_export(input, env);
	else
		ft_printf("command not found: %s\n", input);
	free (input);
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
		free (prompt);
		if (input)
			expand_input(input, env);
		if (ft_strnstr(input, "exit", 4))
			return (rl_clear_history(), free(input), exit(0), 0);
	}
}