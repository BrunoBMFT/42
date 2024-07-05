/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 21:30:07 by bruno             #+#    #+#             */
/*   Updated: 2024/07/05 17:35:05 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*update_prompt()
{
	char	cwd[100];
	char	*dir;
	char	*prompt;
	char	**folders;
	int		i;
	
	dir = getcwd(cwd, sizeof(cwd));//error check
	folders = ft_split(dir, '/');//error check
	i = 0;
	while (folders[i])
		i++;
	prompt = folders[i - 1];
	prompt = ft_strjoin(prompt, " -> ");//error check
	ft_split_free(folders);
	return (prompt);
}

// int for single vs double quotes
// echo 'hello $USER'
// hello $USER
// echo "hello $USER"
// hello bruno

//dont have to worry about spaces
// * $$ gives the shell pid, how to prevent???
// TODO error code implementation, make it so error code expands here
char	*expand_env_vars(char *input, char **env)
{
	int i = 0, j;//use pointers instead?
	bool	flag = false;//flag is to skip the case which it finds a env variable when it wasnt declared (USER without the $ before)
	char	**vars = ft_split(input, '$');//error check
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
			while (env[j] && ft_strnstr(env[j], vars[i], ft_strlen(vars[i])) == 0)
				j++;
			if (!env[j])
				return (NULL);//if no env var, print newline
			vars[i] = ft_strrem(env[j], vars[i]);//error check
			vars[i] = ft_strrem(vars[i], "=");//error check
		}
		if (!output)
			output = ft_strdup(vars[i]);//error check
		else
			output = ft_strjoin(output, vars[i]);//error check
		i++;
	}
	if (input[ft_strlen(input) - 1] == '$')//! dont hardcode like this
		ft_strcat(output, "$");
	ft_split_free(vars);
	return (output);
}

