/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:58:29 by brfernan          #+#    #+#             */
/*   Updated: 2024/05/17 18:22:06 by bruno            ###   ########.fr       */
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
# define WRONGHEREDOC "wrong: ./pipex_bonus here_doc LIMITER cmd cmd1 file"

char	*find_path(char **envp, char *com);
void	error(char *str, int code);
void	freecoms(char **com);
int		execute(char *arg, char **envp);

int		pipex_get_next_line(char **line);

#endif