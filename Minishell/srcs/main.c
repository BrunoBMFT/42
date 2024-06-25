/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 20:13:16 by bruno             #+#    #+#             */
/*   Updated: 2024/06/25 10:59:18 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
//fds for every print function

void	caught_echo(char **vars, char **envp)
{
	int	i = 1;
	if (!vars[1])
		return ;
	while (vars[i])
	{
		ft_putstr_fd(vars[i], 1);
		if (vars[i + 1])//check for last string
			write(1, " ", 1);
		i++;
	}
	
}

char *expand_env_vars(char *input, char **envp)
{
	char	*new = NULL;
	char	**vars = ft_split(input, ' ');
	int i = 0;
	while (vars[i])
	{
		int j = 0;
		while (vars[i][j])
		{
			if (vars[i][j] == '$')// take care of he$USER
			{
				vars[i] = ft_strtrim(vars[i], "$");
				int k = 0;
				while (envp[k] && k < 52)
				{
					if (ft_strnstr(envp[k], vars[i], ft_strlen(vars[i])))
					{
						vars[i] = ft_strtrim(envp[k], vars[i]);
						vars[i] = ft_strtrim(vars[i], "=");
					}
					k++;
				}
			}
			j++;
		}
		if (!new)
			new = ft_strdup(vars[i]);
		else
		{
			new = ft_strjoin(new, " ");
			new = ft_strjoin(new, vars[i]);
		}
		i++;
	}	
	return (new);
}

void	parse_input(char *input, char **envp)//not parsing, it's more like expander
{
	ft_printf("%s\n", input);
	if (!(parse_quotation_mark(input)))
		return ;//error
	input = expand_env_vars(input, envp);
	if (!input)
		return ;
	ft_printf("%s", input);
}

int	main(int ac, char **av, char **envp)
{
	char	*input;

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