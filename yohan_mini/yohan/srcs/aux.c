/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 19:15:54 by bruno             #+#    #+#             */
/*   Updated: 2024/07/10 17:43:35 by bruno            ###   ########.fr       */
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
	if (ft_strnstr(job->cmd, "cd", 2))// fix to use execd
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
	prompt = ft_strjoin(prompt, "$ ");//error check
	free_array(folders);
	return (prompt);
}

t_jobs *build(char *command_line)
{
	t_jobs *jobs;
	t_token *list;

	list = NULL;
	jobs = NULL;
	tokenize(&list, command_line);
	make_job_list(&jobs, &list);
	clear_list(&list);
	return (jobs);
}