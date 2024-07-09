/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 16:38:21 by ycantin           #+#    #+#             */
/*   Updated: 2024/07/09 19:16:31 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL
# define MINISHELL

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

# define    TOKEN_WORD  0 
# define    TOKEN_PIPE  1
# define    TOKEN_AND   2
# define    TOKEN_OR    3
# define    TOKEN_REDIR 4
# define    ERROR      -1 

typedef struct s_holder
{
    int i;
    int j;
    int wc;
    int k;
    char **array;
}t_holder;

typedef struct s_token
{
    char                *token;
    int                 pos;
    int                 type;
    struct  s_token     *prev;
    struct  s_token     *next;
}                       t_token;

typedef struct s_jobs
{
    int             type;
    char            *cmd;
    char            *execd;
    struct s_jobs   *next;
}                   t_jobs;

//bruno:
char	*update_prompt();



//free:
void	clear_list(t_token **lst);

char        **token_array(char *str);
void        tokenize(t_token **list, char *str);
int	        define_type(char *str);
void	    free_all(t_token **list, char **array, char *message, int len);
//lexer:
t_token	    *addtok(void *content);
t_token	    *get_last_tok(t_token *lst);
void	    go_to_next(t_token **lst, t_token *new);
int         peek_next(t_token *list);

char        *full_cmd(t_token **cur);
int         give_type(t_token *token);
t_jobs	    *addjob(void *content);
t_jobs	    *get_last_job(t_jobs *lst);
void	    go_to_next_job(t_jobs **lst, t_jobs *new); 
void        make_job_list(t_jobs **job_list, t_token **tok_list);
void	    clear_jobs(t_jobs **lst);


#endif