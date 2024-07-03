/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 20:13:16 by bruno             #+#    #+#             */
/*   Updated: 2024/07/03 19:53:41 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
// ! Error exit codes
// * ERROR CHECK EVERY MALLOC FUNCTION
// * change everything to fd functions
// TODO check return codes for getcwd, chdir, readline
// TODO make a function to find env variables (less use of strnstr(env, env_var))
// * parse things like envf or pwde


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
//	else if (ft_strnstr(input, "export", 6))
//		caught_pwd(input, env);
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