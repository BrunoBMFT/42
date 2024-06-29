/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 20:13:16 by bruno             #+#    #+#             */
/*   Updated: 2024/06/30 00:00:18 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
//"cd FOLDER"
//parsing of folder existing or not to be decided
// ! problem... case: folder named pwD, output is pw (D gets trimmed) (env_vars)
void	caught_cd(char *input, char **envp)
{
	char *test = ft_strtrim(input, "cd");
	printf("%s\n", test);
}

void	parse_input(char *input, char **envp)//not parsing, it's more like expander
{
//	ft_printf("%s\n", input);
	
	input = expand_env_vars(input, envp);
	if (!input)
		return ;
	if (ft_strnstr(input, "echo", 4))
		caught_echo(input);
	if (ft_strnstr(input, "cd", 4))
		caught_cd(input, envp);

//	ft_printf("expanded:\n%s", input);//expander test
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