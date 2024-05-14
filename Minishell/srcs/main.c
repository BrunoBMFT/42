/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 20:13:16 by bruno             #+#    #+#             */
/*   Updated: 2024/05/13 22:38:59 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	caught_cd(char *str)
{
	char	**split;
	int	i;

	split = ft_split(str, ' ');
	i = 0;
	while (split[i])
		i++;
	if (i < 2)
		ft_putendl("too few arguments");
	if (i > 2)
		ft_putendl("too many arguments");
	
}

void	caught_args(char *str)
{
	if (ft_strnstr(str, "cd", 2))
	{
		ft_putendl("caught cd");
		caught_cd(str);
	}
}

int	main(int ac, char **av, char **envp)
{
	char scan[100];
	while (1)
	{
		ft_printf("minishell -> ");
		scanf("%s", scan);
		caught_args(scan);
		ft_printf("%s\n", scan);
	}
}