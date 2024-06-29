/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 20:13:16 by bruno             #+#    #+#             */
/*   Updated: 2024/06/29 12:22:10 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	caught_echo(char *input)
{
	int i = 4;
	while (input[i] == ' ' || input[i] == '\t')
		i++;
	while (input[i])
	{
		write(1, &input[i], 1);
		i++;
	}
}
// int for single vs double quotes
// echo 'hello $USER'
// hello $USER
// echo "hello $USER"
// hello bruno

//dont have to worry about spaces
// * $$ gives the shell pid, how to prevent???
char	*expand_env_vars(char *input, char **envp)
{
	int i = 0, j;
	bool	flag = false;//flag is to skip the case which it finds a env variable when it wasnt declared (USER without the $ before)
	char	**vars = ft_split(input, '$');
	char	*output = NULL;
	if (input[0] != '$')
		flag = true;

	while (vars[i])
	{
		if (flag)
			flag = false;
		else
		{
			j = 0;
			while (envp[j])
			{
				if (ft_strnstr(envp[j], vars[i], ft_strlen(vars[i])))
				{
					vars[i] = ft_strtrim(envp[j], vars[i]);
					vars[i] = ft_strtrim(vars[i], "=");
				}
				j++;
			}
		}
		if (!output)
			output = ft_strdup(vars[i]);
		else
			output = ft_strjoin(output, vars[i]);
		i++;
	}
	if (input[ft_strlen(input) - 1] == '$')
		ft_strcat(output, "$");
	return (output);
}


void	parse_input(char *input, char **envp)//not parsing, it's more like expander
{
//	ft_printf("%s\n", input);
	
	if (ft_strnstr(input, "echo", 4))
		caught_echo(input);

	input = expand_env_vars(input, envp);
	if (!input)
		return ;
	ft_printf("expanded:\n%s", input);//expander test
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_shell	shell;

	shell.env = envp;

	while (1)
	{
		input = readline("minishell -> ");
		if (input)
			parse_input(input, envp);
		if (ft_strnstr(input, "exit", 4))
			return (rl_clear_history(), free(input), exit(0), 0);
		ft_nl_fd(1);
	}
}