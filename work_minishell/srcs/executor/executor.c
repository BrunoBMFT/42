/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:26:33 by bruno             #+#    #+#             */
/*   Updated: 2024/10/24 19:49:25 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	executor_input(t_jobs *job, t_env *env)//return values negligeble?
{
	int	redirected_input;

/* 
	if (job->input && (job->input[0] == '$'))// TODO for now commented, messes up apply_redir
	{
//		*status = 1;
//		return (ft_printf_fd(2, "minishell: %s: ambiguous redirect\n", job->input), -1);
	} */
	redirected_input = open(job->input, O_RDONLY);
	if (ft_strcmp("/dev/null", job->input) == 0)//not being saved?
		env->status = 1;
	dup2(redirected_input, STDIN_FILENO);
	close(redirected_input);
	return (0);
}

int	executor_output(t_jobs *job, int *status)//return values negligeble
{
	int	redirected_output;

	// if (job->output && (job->output[0] == '$'))
	// {
	// 	ft_printf_fd(2, "minishell: %s: ambiguous redirect\n", job->output);
	// 	job->output = ft_strdup("/dev/null");
	// }
	if (job->append)
		redirected_output = open(job->output, O_CREAT | O_APPEND | O_RDWR, 0644);
	else
	{
		if (access(job->output, F_OK) == 0)
			remove(job->output);
		redirected_output = open(job->output, O_CREAT | O_RDWR, 0644);
	}
	if (ft_strcmp("/dev/null", job->output) == 0)
		*status = 1;
	dup2(redirected_output, STDOUT_FILENO);
	close(redirected_output);//else
	return (0);
}
//not needed?
int    count_processes(t_jobs **jobs)
{
    int		i;
    t_jobs *job;

    i = 0;
    job = *jobs;
    while (job)
    {
        if (job->type == PIPE || job->job)
            i++;
        job = job->next;
    }
    return (i + 1);
}

void	start_executor(t_jobs *job, t_env *env)
{
//	signal(SIGINT, handle_signal_child);
//	signal(SIGQUIT, sigquit);
	env->saved_stdin = dup(STDIN_FILENO);
	env->saved_stdout = dup(STDOUT_FILENO);
	env->pids = ft_calloc_pids(sizeof(int), count_processes(&job));//error check
	while (job)
	{
		//expanding
		if (job->job)
			modify_array(job->job, env);
		//redirections
		if (job->input)
			executor_input(job, env);
		if (job->output)
			executor_output(job, &env->status);
//		printf("env status before processes: %d\n", env->status);

		
		//pipes
		if (job->next && job->next->type == PIPE)
		{
			env->status = child_process(job, env);
			job = job->next->next;
			job->piped = true;
			continue;
		}

		
		//executing jobs
		else if (job->job && job->job[0] && job->piped)
			env->status = child_process(job, env);//builtins status check
		else if (job->job && job->job[0])
			simple_process(job, env);//builtins status check
		int i = 0;
		while (env->pids[i])
		{
			printf("is running\n");
			waitpid(env->pids[i], &env->status, 0);
			i++;
		}
//		printf("env status after processes: %d\n", env->status);



		//resets
		dup2(env->saved_stdin, STDIN_FILENO);
		dup2(env->saved_stdout, STDOUT_FILENO);
		if (job->heredoc_file && access(job->heredoc_file, F_OK) == 0)
			remove(job->heredoc_file);



		//operators
		if (job->next && job->next->type == AND)
		{
			job = job->next->next;
			job->piped = false;
		}
		else if (job->next && job->next->type == OR)
		{
			if (env->status == 0)
			{
				while(job->next && job->next->type == OR)
					job = job->next->next;
				if (job->next)
					job = job->next->next;
				else
					job = job->next;
			}
			else
				job = job->next;
			job->piped = false;
		}
		else
			job = job->next;
	}
	if (access(".heredoc", F_OK) == 0)
		remove(".heredoc");
	close(env->saved_stdin);
	close(env->saved_stdout);
	return ;
}
