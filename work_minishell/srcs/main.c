/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 16:43:23 by ycantin           #+#    #+#             */
/*   Updated: 2024/07/23 16:49:39 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main (int ac, char **av, char **envp)
{
	char	**env = envp;
	char	*line;
	char	*dir;
	char	*prompt;
	t_jobs	*jobs;
	char	**temp_vars = NULL;
	while (1)
	{
		prompt = update_prompt();
//		if (set_up_signal(ctrl_c_idle) < 0)
//			clean_exit(jobs, line, prompt);
		line = readline(prompt);
		free(prompt);
//		line = expand_env_vars(line, env);
//		printf("line: %s\n", line);
		check_exit(line);
		add_history(line);
		jobs = build(line);
//		if (ft_strnstr(jobs->cmd, "=", ft_strlen(jobs->cmd)))//cmd: "export=" doesnt export or save anything
//			temp_vars = variable_declaration(jobs->job, temp_vars);
		start_executor(jobs, env);
//		free(prompt);
//		clear_jobs(&jobs);//edited by bruno
	}
	return (0);
}
