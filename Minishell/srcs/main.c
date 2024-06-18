/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 20:13:16 by bruno             #+#    #+#             */
/*   Updated: 2024/06/19 00:09:58 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	caught_echo(char *input, char **envp)
{
	
}

void	parse_input(char *input, char **envp)
{
	char	**command;

	command = ft_split(input, ' ');
	if (command[0] == "echo")
	{
		ft_printf("hello");
	}
	ft_split_free(command);
}

int	main(int ac, char **av, char **envp)
{
	char	*input;

	while (1)
	{
		input = readline("minishell -> ");
		parse_input(input, envp);
		if (input[0] == '$')
			caught_env_variable(input, envp);
		else
			ft_printf("%s\n", input);
	} 
}