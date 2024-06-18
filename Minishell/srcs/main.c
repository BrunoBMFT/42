/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 20:13:16 by bruno             #+#    #+#             */
/*   Updated: 2024/06/18 17:09:07 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	caught_echo(char *input, char **envp)
{
	
}

int	main(int ac, char **av, char **envp)
{
	char	*input;

	while (1)
	{
		input = readline("minishell -> ");
		if (input[0] == '$')
			caught_env_variable(input, envp);
		else
			ft_printf("%s\n", input);
	} 
}