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

//done
int	caught_env_variable(char *env_var, char **envp);




void	freecoms(char **cmd);
void	change_dir(char **envp, char *dir);
#endif