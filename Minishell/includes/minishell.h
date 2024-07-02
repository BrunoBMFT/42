#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include  <signal.h>
# include <readline/readline.h>

# define WRITE 1
# define READ 0

# define BEFORE 0
# define AFTER 1

//done
char	*expand_env_vars(char *input, char **env);
void	caught_echo(char *input);


void	expand_input(char *input, char **envp);
bool	parse_quotation_mark(char *input);
void	freecoms(char **cmd);
void	caught_exit_status();
void	update_pwd(char **env, bool when);
void	caught_pwd(char **env);
char	*update_prompt();

//pipex
bool	execute(char *arg, char **envp);
char	*find_path(char **envp, char *com);
void	freecoms(char **cmd);//can change for split_free

#endif