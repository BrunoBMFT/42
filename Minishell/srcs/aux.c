/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 21:30:07 by bruno             #+#    #+#             */
/*   Updated: 2024/06/30 00:00:04 by bruno            ###   ########.fr       */
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
// ! problem... case: folder named pwD, output is pw (D gets trimmed)
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
					vars[i] = ft_strtrim(envp[j], vars[i]);//problem... case: folder named pwD, output is pw (D gets trimmed)
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

void	caught_exit_status()
{
	ft_putendl_fd("nice exit code expanded here", 1);//stdout?
}

bool	parse_quotation_mark(char *input)
{
	int	closed1;
	int	closed2;

	closed1 = 0;
	closed2 = 0;
	int	i = 0, j = 0;
	while (input[i])
	{
		if (input[i] == 34)// int for "
			closed1++;
		else if (input[i] == 39)// int for '
			closed2++;
		else
		{
			input[j] = input[i];
			j++;
		}
		i++;
	}
	i = 0;
	while (i < closed1 || i < closed2)
	{
		input[j] = 0;
		i++;
	}
	if (ft_is_even(closed1) && ft_is_even(closed2))
		return (true);
	return (false);
}
