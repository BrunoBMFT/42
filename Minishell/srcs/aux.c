/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 21:30:07 by bruno             #+#    #+#             */
/*   Updated: 2024/07/02 00:48:16 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*update_prompt()
{
	char	cwd[100];
	char	*prompt;
	char	*dir;
	
	dir = getcwd(cwd, sizeof(cwd));//error check
	char	**folders = ft_split(dir, '/');
	int i = 0;
	while (folders[i])
		i++;
	prompt = folders[i - 1];
	prompt = ft_strjoin(prompt, " -> ");//error check
	ft_split_free(folders);
	return (prompt);
}

void	caught_echo(char *input)
{
	int		i;
	bool	nl;	
	
	nl = true;
	if (ft_strnstr(input, "-n", 7))
	{
		nl = false;
		i = 7;
	}
	else
		i = 4;
	while (input[i] == ' ' || input[i] == '\t')
		i++;
	while (input[i])
	{
		write(1, &input[i], 1);
		i++;
	}
	if (nl == true)
		ft_nl_fd(1);
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
					vars[i] = ft_strrem(envp[j], vars[i]);
					vars[i] = ft_strrem(vars[i], "=");
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
