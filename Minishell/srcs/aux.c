/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 21:30:07 by bruno             #+#    #+#             */
/*   Updated: 2024/07/10 00:27:57 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	panic(char *s)
{
	ft_putendl_fd(s, 2);
	exit(1);
}

int	new_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		panic("fork");
	return (pid);
}

bool	execute_builtins(char *command, char **env)
{
	if (ft_strnstr(command, "cd", 2))
		return (caught_cd(command, env), true);
	else if (ft_strnstr(command, "echo", 4))
		return (caught_echo(command), true);
	else if (ft_strnstr(command, "env", 3))
		return (caught_env(command, env), true);
	else if (ft_strnstr(command, "pwd", 3))
		return (caught_pwd(command, env), true);
	return (false);
	//not good for the cases where cd fails and returns exit code, fix 
}

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
	if (!input)
		return (NULL);
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
				return (NULL);//print new line
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

