/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 21:30:07 by bruno             #+#    #+#             */
/*   Updated: 2024/07/11 15:23:01 by bruno            ###   ########.fr       */
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

bool	execute_builtins(t_jobs *job, char **env)
{
	if (ft_strnstr(job->cmd, "cd", 2))// if cd fails, env OLDPWD shouldn't update
		return (caught_cd(job, env), true);
	else if (ft_strnstr(job->cmd, "echo", 4))// fix to use execd
		return (caught_echo(job), true);
	else if (ft_strnstr(job->cmd, "env", 3))
		return (caught_env(job->cmd, env), true);
	else if (ft_strnstr(job->cmd, "pwd", 3))
		return (caught_pwd(job->cmd, env), true);
	return (false);
	//not good for the cases where cd fails and returns exit code, fix 
}

char	*update_prompt()//fix how yohan fixed it
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
	ft_free_array(folders);
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
char	*env_var_return(char *str)//wrong size allocated
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '=')
		i++;
	i++;
	new = ft_calloc(sizeof(char), ft_strlen(str));
	if (!new)
		return (NULL);
	while (str[i])
	{
		new[j] = str[i];
		j++;
		i++;
	}
	return (new);
}

int	len_to_equal(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

char	*expand_env_vars(char *input, char **env)
{
	int 	i;//use pointers instead?
	bool	flag = false;//flag is to skip the case which it finds a env variable when it wasnt declared (USER without the $ before)
	char	**vars = ft_split(input, '$');//error check
	char	*output = NULL;
	char	*temp;

	if (input[0] != '$')
		flag = true;
	while (*vars)//running through each word
	{
		if (flag)
			flag = false;// dont hardcode like this
		else
		{
			i = 0;
			while (env[i])
			{
				temp = ft_strndup(env[i], len_to_equal(env[i]));
				if (ft_strncmp(temp, *vars, ft_strlen(temp)) == 0)
					break;
				i++;
			}
			if (!env[i])
				return (NULL);//print new line
			*vars = env_var_return(env[i]);// error check
		}
		if (!output)
			output = ft_strdup(*vars);//error check
		else
			output = ft_strjoin(output, *vars);//error check
		vars++;
	}
	if (input[ft_strlen(input) - 1] == '$')//! dont hardcode like this
		ft_strcat(output, "$");
//	ft_split_free(vars);
	return (output);
}