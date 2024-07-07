/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 20:13:16 by bruno             #+#    #+#             */
/*   Updated: 2024/07/07 21:04:47 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_path(char *command, char **env)
{
	//use strcmp
	char	**paths;
	char	*path;

	while (*env && ft_strnstr(*env, "PATH", 4) == 0)
		env++;
	if (!*env)
		return NULL;
	paths = ft_split(*env, ':');
	while (*paths)
	{
		*paths = ft_strjoin(*paths, "/");
		path = ft_strjoin(*paths, command);
		if (access(path, F_OK) == 0)
			return (path);
		free (path);
		paths++;
	}
//	ft_split_free(paths);
	return (NULL);
}

bool	execute_job(char *job, char **env)
{
	char	**command = ft_split(job, ' ');
	char	*path = find_path(command[0], env);
	if (!path)
		return false;
	execve(path, command, env);
	printf("execution failed");
	return true;
}

int	child_process(char *job, char **env)
{
	int	pid = new_fork();
	if (pid == 0)
	{
		if (!execute_job(job, env))
			exit(1);//free fds, show exit code and perror
	}
	waitpid(pid, NULL, 0);
}

int	last_process(char *job, char **env)
{
	int	status = 0;
	int	exit_code = 0;
	int	pid = new_fork();
	if (pid == 0)
		if (!execute_job(job, env))
			exit(127);//free fds, show exit code and perror
	waitpid(pid, &status, 0);
	return (status);
}

//only last process gives exit code != 0
int	start_execution(char *input, char **env)//fork here
{
	char	**jobs = ft_split(input, '|');
	int i = 0;
	while (i < ft_split_wordcount(jobs) - 1)//careful with fds
	{
		child_process(jobs[i], env);
		i++;
	}
	last_process(jobs[i], env);//jobs[i] because it's last proc

}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	char	*prompt;
	char	**env;

	env = envp;
	while (1)
	{
		prompt = update_prompt();
		input = readline(prompt);
		free (prompt);
		input = expand_env_vars(input, env);
		if (!input)
			return (0);//free stuff
//		if (!execute_builtins(input, env))
			start_execution(input, env);
		if (ft_strnstr(input, "exit", 4))
			return (rl_clear_history(), free(input), exit(0), 0);
	}
}