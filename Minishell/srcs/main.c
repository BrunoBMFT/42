/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 20:13:16 by bruno             #+#    #+#             */
/*   Updated: 2024/07/11 03:50:21 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char    *find_path(char *command, char **env)
{
	//use strcmp
	char    **paths;
	char    *path;

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
	ft_free_array(paths);
	return (NULL);
}

bool    execute_job(char **command, char **env)
{
	char    *path = find_path(command[0], env);
	if (!path)
		return (printf("no command"), false);//free the commands
	execve(path, command, env);
	printf("execution failed");
	ft_free_array(command);
	return true;
}

int     child_process(char **command, char **env)
{
	int     pid = new_fork();
	if (pid == 0)
	{
		if (!execute_job(command, env))
			panic("execute");//free fds, show exit code and perror
	}
	waitpid(pid, NULL, 0);
}

//only last process gives exit code != 0
int     start_execution(char **command, char **env)//fork here
{
	child_process(command, env);
//		char    **jobs = ft_split(input, '|');
//		int i = 0;
//		while (i < ft_split_wordcount(jobs) - 1)
//		{
//				child_process(job, env);
//				i++;
//		}
//		last_process(jobs[i], env);//jobs[i] because it's last proc
	return (0);
}

int main (int ac, char **av, char **envp)
{
	char *line = NULL;
	char *dir = NULL;
	char *prompt = NULL;
	t_jobs *jobs = NULL;
	t_jobs *curr;
	char **env = envp;


	while (1)
	{
		prompt = update_prompt();
		line = readline(prompt);
		free(prompt);
		add_history(line);
		if (!line)
			continue;//free stuff
		line = expand_env_vars(line, env);
		if (!line)
			continue;//free stuff
		jobs = build(line);
		curr = jobs;
		int i = 0, j;
		while (curr != NULL)
		{
			char **command = job_array(curr);
			if (curr->type < 0)
				curr->type = 0;
	//		execute_builtins(curr, env);
			if (!execute_builtins(curr, env))
				start_execution(command, env);//errors codes
	//		printf("cmd: %s     execd:  %s   type: %d\n", curr->cmd, curr->execd, curr->type);
	/* 		printf("%s  %s  %d\n", curr->cmd, curr->execd, curr->type);
			if (curr->job)
			{
				j = 0;
				while (curr->job[j])
				{
					printf("->%s    %d\n", curr->job[j], i);
					j++;
				}
			} */
			curr = curr->next;
		}
		i++;
		free(prompt);
	//        clear_jobs(&jobs);
		if (ft_strcmp(line, "exit") == 0)
				return (rl_clear_history(), free(line), exit(0), 0);
	}
	return (0);
}