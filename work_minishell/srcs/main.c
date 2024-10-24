/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 16:43:23 by ycantin           #+#    #+#             */
/*   Updated: 2024/10/24 16:44:41 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_jobs(char *line, t_jobs *jobs)
{
	printf("line: %s\n", line);
	int i = 0;
	while (jobs->job[i])
	{
		ft_printf_fd(2, "job %d: %s\n", i, jobs->job[i]);
		i++;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env	env;
	t_jobs	*jobs;
	t_jobs	*curr;
	char	*line;
	char	*dir;

	// if (!envp || !envp[0])
	// {
	// 	ft_printf_fd(2, "you dirty, dirty evaluator...\nDid you really think you could run our code without an environment?\nHuzzah! No further\n");
	// 	return (1);
	// }
	env = init_env(envp);
	while (1)
	{
//		signal(SIGINT, handle_signal_main);
//		signal(SIGQUIT, SIG_IGN);
		choose_signal(ROOT_SIG);
		// env.prompt = update_prompt();
		// line = readline(env.prompt);
		line = readline("Minishell> ");
		free(env.prompt);
		if (!line)
			ctrld(line, &env);
		if (secondquote(line) == 1)	//remove if you want to request additional info to finish prompt
		{
			free(line);
			ft_printf("error: unclosed quote\n");
			continue ;
		}
		add_history(line);
		line = parse_quotes(line);//not working correctly?
		jobs = build(line, env);
		if (!jobs)
			continue ;
		curr = jobs;//why use curr?
		start_executor(curr, &env);
		clear_jobs(&jobs);
	}
	return (0);
}
