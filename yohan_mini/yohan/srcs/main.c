/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 16:43:23 by ycantin           #+#    #+#             */
/*   Updated: 2024/07/11 00:41:18 by bruno            ###   ########.fr       */
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
	free_array(paths);
	return (NULL);
}

bool	execute_job(char **command, char **env)
{
	char	*path = find_path(command[0], env);
	if (!path)
		return (printf("no command"), false);//free the commands
	execve(path, command, env);
	printf("execution failed");
	free_array(command);
	return true;
}

int	child_process(char **command, char **env)
{
	int	pid = new_fork();
	if (pid == 0)
	{
		if (!execute_job(command, env))
			panic("execute");//free fds, show exit code and perror
	}
	waitpid(pid, NULL, 0);
}

//only last process gives exit code != 0
int	start_execution(char **command, char **env)//fork here
{
	child_process(command, env);

//	char	**jobs = ft_split(input, '|');
//	int i = 0;
//	while (i < ft_split_wordcount(jobs) - 1)
//	{
//		child_process(job, env);
//		i++;
//	}
//	last_process(jobs[i], env);//jobs[i] because it's last proc
	return (0);
}

char **job_array(t_jobs *node)
{
	char **array;
	char *str;
	char *temp;
	char *new_last;
	int i;

	i = 0;
	str = ft_strdup(node->cmd);
	temp = ft_strjoin(str, " '");
	free(str);
	if (node->execd)
	{
		str = ft_strjoin(temp, node->execd);
		free(temp);
		temp = ft_strjoin(str, "'");
		free(str);
	}
	array = token_array(temp);
	free(temp);
	while (array[i])
		i++;
	if (i > 0) 
	{
		new_last = ft_strdup(array[i - 1]);
		free(array[i - 1]);
		array[i - 1] = ft_strtrim(new_last, "'");
		free(new_last);
	}
	return (array);
}

int main (int ac, char **av, char **envp)
{
	char	**env = envp;
	char	*line;
	char	*dir;
	char	*prompt;
	t_jobs	*jobs;
	t_jobs	*curr;
	while (1)
	{
		prompt = update_prompt();
		line = readline(prompt);
		free(prompt);
		add_history(line);
		jobs = build(line);
		curr = jobs;
		int i = 0;
		while (curr != NULL)
		{
/* 			char **command = job_array(curr);
			int i = 0;
			while (command[i])
			{
				printf("%s\n", command[i]);
				i++;
			} */
			if (curr->type < 0)
				curr->type = 0;

			if (!(execute_builtins(curr, env)))//errors codes
			{
				printf("no");
			}
//				start_execution(command, env);//error codes
//			printf("cmd: %s     execd:  %s   type: %d\n", curr->cmd, curr->execd, curr->type);
			curr = curr->next;
		}
//		free(prompt);
//		clear_jobs(&jobs);
		if (ft_strcmp(line, "exit") == 0)
		{
			free(line);
			break;
		}
	}
	return (0);
}


/* 
int main(void)
{
	char *str = "cat file.txt | sort > output.txt && grep 'search' output.txt && echo done";
	t_jobs *jobs;
	jobs = build(str);
	t_jobs *currr = jobs;
	int i = 0;
	while (currr != NULL)
	{
		i++;
		printf("%s  %s\n", currr->cmd, currr->execd);
		currr = currr->next; 
	}
	clear_jobs(&jobs);
} */