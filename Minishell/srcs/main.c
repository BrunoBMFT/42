/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 20:13:16 by bruno             #+#    #+#             */
/*   Updated: 2024/06/22 01:34:33 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
//fds for every print function
//expand $USER$USER


// ! not working lol
int	caught_env_variable(char *vars, char **envp, int start)
{
	char	**env_variable;
	int i = 0, j;
	
	env_variable = ft_split(vars, '$');
	while (env_variable[i])
	{
		j = 0;
		while (envp[j] && j < 40)
		{
			if (ft_strnstr(envp[j], vars, ft_strlen(vars)))
			{
				env_variable[i] = ft_strtrim(envp[j], env_variable[i]);
				env_variable[i] = ft_strtrim(env_variable[i], "=");
				break;
			}
			j++;
		}
		if (env_variable[i])
			printf("%s", env_variable[i]);
		i++;
	}
	return (1);
}

void	parse_input(char *input, char **envp)
{
//	ft_printf("%s\n", input);
	if (!(parse_quotation_mark(input)))
		return ;
		
	char	**vars = ft_split(input, ' ');
	int i = 0, j;
	while (vars[i])
	{
		j = 0;
		while (vars[i][j])
		{
			if (vars[i][j] == '$')
				caught_env_variable(vars[i], envp, j);
			j++;
		}
		i++;
	}
	
	ft_split_free(vars);
}

int	main(int ac, char **av, char **envp)
{
	char	*input;

	while (1)
	{
		input = readline("minishell -> ");
		if (input)
			parse_input(input, envp);
		ft_nl();
	} 
}