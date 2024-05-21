/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 20:13:16 by bruno             #+#    #+#             */
/*   Updated: 2024/05/21 18:10:40 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_program(char *str)
{
	ft_putstr(str);
	exit (0);
}

void	caught_cd(char *str, char **envp)
{
	char	**split;
	int	i;

	split = ft_split(str, ' ');
	i = 0;
	while (split[i])
		i++;
	if (i < 2 || i > 2)
		ft_putendl("wrong number of arguments");
	
	i = 0;
	while (ft_strnstr(envp[i], "PWD", 3) == 0)
		i++;
	
		
}


void	caught_args(char *str, char **envp)
{
	if (ft_strnstr(str, "cd", 2))
		caught_cd(str, envp);
	if (ft_strnstr(str, "exit", 4))
		exit_program(str);
}

int	main(int ac, char **av, char **envp)
{
	char scan[100];
	while (1)
	{
		ft_printf("minishell -> ");
		fgets(scan, 100, stdin);
		caught_args(scan, envp);
//		ft_printf("%s\n", scan);
	}
}