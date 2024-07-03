#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <signal.h>
# include <readline/readline.h>

# define WRITE 1
# define READ 0

# define BEFORE 0
# define AFTER 1

//done
char	*expand_env_vars(char *input, char **env);
void	caught_cd(char *input, char **env);
void	caught_echo(char *input);
void	caught_env(char	*input, char **env);
void	caught_pwd(char *input, char **env);


void	expand_input(char *input, char **envp);
void	freecoms(char **cmd);
void	update_pwd(char **env, bool when);
char	*update_prompt();


//pipex
bool	execute(char *arg, char **envp);
char	*find_path(char **envp, char *com);
void	freecoms(char **cmd);//can change for split_free

#endif