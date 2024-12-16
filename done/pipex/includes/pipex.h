/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:58:29 by brfernan          #+#    #+#             */
/*   Updated: 2024/12/16 04:02:10 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>

# define WRONG "wrong: ./pipex <file1> <cmd1> <cmd2> <file2>"
# define WRONGBONUS "wrong: ./pipex_bonus file1 cmd1 cmd2 cmd3 ... cmdn file2"
# define NOENV "No environment loaded"
# define WRITE 1
# define READ 0

typedef struct s_pipex
{
	// char **envp;
	pid_t	*pids;
}				t_pipex;


char	*find_path(char **envp, char *com);//fix how bonus uses it
void	error(int code);
void	error2(char *str, int code, int *fd);
bool	execute(char *arg, char **envp);
void	close_fds_exit(int *fd);
//aux
int		new_fork(t_pipex *pipex);
void	*ft_calloc_pids(int size);
int		run_waitpids(t_pipex *pipex);


#endif