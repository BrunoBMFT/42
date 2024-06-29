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

typedef	struct	s_shell
{
	char	**env;
}				t_shell;


//done
char	*expand_env_vars(char *input, char **envp);
void	caught_echo(char *input);


bool	parse_quotation_mark(char *input);
void	freecoms(char **cmd);
void	caught_exit_status();
#endif