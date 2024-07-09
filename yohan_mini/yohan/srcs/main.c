/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 16:43:23 by ycantin           #+#    #+#             */
/*   Updated: 2024/07/09 21:54:09 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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


bool	execute_builtins(t_jobs *job, char **env)
{
	if (ft_strnstr(job->cmd, "cd", 2))
		return (caught_cd(job->cmd, env), true);
	else if (ft_strnstr(job->cmd, "echo", 4))// fix to use execd
		return (caught_echo(job->cmd), true);
	else if (ft_strnstr(job->cmd, "env", 3))
		return (caught_env(job->cmd, env), true);
	else if (ft_strnstr(job->cmd, "pwd", 3))
		return (caught_pwd(job->cmd, env), true);
	return (false);
	//not good for the cases where cd fails and returns exit code, fix 
}

int main (void)
	{
	char *line;
	char *dir;
	char *prompt;
	t_jobs *jobs;
	t_jobs *curr;
	while (1)
	{
		prompt = update_prompt();
		free(prompt);
		line = readline(prompt);
		add_history(line);
		jobs = build(line);
		curr = jobs;
		while (curr != NULL)
		{
			



			if (curr->type < 0)
				curr->type = 0;
//			printf("cmd: %s     execd:  %s   type: %d\n\n", curr->cmd, curr->execd, curr->type);
			curr = curr->next; 
		}
		free(prompt);
		clear_jobs(&jobs);
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
        //   "echo hello";
         //"echo hello && ls -la";
         //"cat file.txt | grep 'search' > output.txt";
        // "echo hello && ls -la || echo world";
         //"cat file.txt | grep 'search' | sort > output.txt";
         //"command -option1 -option2";
         //"echo hello && ls -la || echo world && echo again";
        // "cat file.txt | grep 'search' > output.txt && echo done";
        // "command -option1 | command2 -option2 > file";
        // "echo hello > file && cat file";
        // "echo hello && echo world || echo universe";
      //   "command1 && command2 || command3 && command4";
       //  "cat file.txt | grep 'search' | sort | uniq";
      //  "echo hello > file.txt && cat file.txt | grep hello";
       //  "command1 | command2 && command3 || command4";
       // "ls -la | grep 'file' > output.txt";
        // "echo hello && (echo world || echo universe)";
       //  "command1 && command2 || command3 > file.txt";
     //   "cat file.txt > output.txt | grep 'search'";
      //  "echo hello > file1 && cat file1 | sort > file2";
        //"command1 && command2 && command3 || command4";
       // "echo hello || echo world && echo universe";
      //   "command1 | command2 | command3 > file";
    //     "cat file.txt > output1.txt && sort output1.txt > output2.txt";
    //     "echo hello > file && echo world >> file";
    //     "command1 && command2 || command3 | command4";
    //     "cat file.txt | sort > output.txt && grep 'search' output.txt";
    //     "echo hello > file && cat file || echo failed";
    //     "command1 -option1 | command2 -option2 > file";
    //     "ls -la && echo done || echo failed";
    //     "echo hello || echo world && echo universe > file";
    //     "cat file1 | grep 'search' | sort > file2 && echo done";
    //     "command1 && command2 || command3 | command4 > file";
    //     "echo hello && ls -la || echo world && cat file";
    //     "cat file.txt | grep 'search' | sort | uniq > output.txt";
    //     "echo hello > file.txt && cat file.txt | grep hello | sort";
    //     "command1 && command2 || command3 && command4 || command5";
    //     "ls -la | grep 'file' > output.txt && echo done";
    //     "echo hello && (echo world || echo universe) && echo end";
    //     "command1 && command2 || command3 > file.txt && echo done";
    //     "cat file.txt > output.txt | grep 'search' | sort";
    //     "echo hello > file1 && cat file1 | sort > file2 && echo done";
    //     "command1 && command2 && command3 || command4 | command5";
    //     "echo hello || echo world && echo universe > file && cat file";
    //     "command1 | command2 | command3 > file && echo done";
    //     "cat file.txt > output1.txt && sort output1.txt > output2.txt && echo done";
    //     "echo hello > file && echo world >> file && cat file";
    //     "command1 && command2 || command3 | command4 && command5";
    //     "cat file.txt | sort > output.txt && grep 'search' output.txt && echo done;
