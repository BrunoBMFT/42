/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 19:13:31 by bruno             #+#    #+#             */
/*   Updated: 2024/10/25 04:32:49 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	new_fork()
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		ft_printf_fd(2, "fork() error\n");
		return (-1);
	}
	return (pid);
}

void	child_process(t_jobs *job, t_env *env)// ! signals
{
	int		fd[2];

	pipe(fd);//error check?
	int i = 0;
	while (env->pids[i] != -1)
		i++;
	env->pids[i] = new_fork();
	if (env->pids[i] < 0)
		return (env->status = 1, (void)NULL);
	if (env->pids[i] == 0)
	{
		close(fd[READ]);
		if (!job->output && job->next && job->next->type == PIPE)//checks whether it is last statement or not
			dup2(fd[WRITE], STDOUT_FILENO);//error check
		else if (!job->output)
			dup2(env->saved_stdout, STDOUT_FILENO);//error check
		close(fd[WRITE]);
		env->status = try_builtins(job, env, false);
		if (env->status == 200)
			execute_job(job, env);
		clean_exit(job, env, env->status);//env.status
	}
	close(fd[WRITE]);
	dup2(fd[READ], STDIN_FILENO);//error check
	close(fd[READ]);
	return ;
}

void	simple_process(t_jobs *job, t_env *env)
{
	pid_t	pid;
	int		status;

	choose_signal(IGNORE_SIG);
	if (job->job && job->job[0] && (ft_strcmp(job->job[0], "cd")) == 0)//a few of this checks are done before
		return (caught_cd(job, env));//fix exit status and return value
	env->status = try_builtins(job, env, false);
	if (env->status != 200)
		return ;
	pid = new_fork();//fork with env pids?
	if (pid < 0)
		return (env->status = 1, (void)NULL);
	if (pid == 0)
		execute_job(job, env);//error check?
	waitpid(pid, &status, 0);//feels like it can be here, but should i do it outside??
	env->status = WEXITSTATUS(status);
	return ;
}
