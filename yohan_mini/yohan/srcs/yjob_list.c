/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yjob_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 18:20:43 by ycantin           #+#    #+#             */
/*   Updated: 2024/07/10 21:17:43 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *full_cmd(t_token **cur)
{
    char *job;
    char *temp;

    if (!(*cur) || (*cur)->type != TOKEN_WORD)
        return NULL;

    job = ft_strdup((*cur)->token);
    *cur = (*cur)->next;

    while (*cur && (*cur)->type == TOKEN_WORD && (*cur)->token[0] == '-')
    {
        temp = ft_strjoin(job, " ");
        free(job);
        job = ft_strjoin(temp, (*cur)->token);
        free(temp);
        *cur = (*cur)->next;
    }

    return job;
}

char *get_execd(t_token **cur)
{
    char *execd;
    char *temp;
    
    execd = ft_strdup((*cur)->token);
    *cur = (*cur)->next;

    while (*cur && (*cur)->type == TOKEN_WORD)
    {
        if (!(*cur) || (*cur)->type != TOKEN_WORD)
            break;
        temp = ft_strjoin(execd, " ");
        free(execd);
        execd = ft_strjoin(temp, (*cur)->token);
        free(temp);
        *cur = (*cur)->next;
    }
    return (execd);
}


void make_job_list(t_jobs **job_list, t_token **tok_list)
{
    t_token *cur;
    t_jobs *new;
    char *cmd;

    cur = *tok_list;
    while (cur)
    {
        new = addjob(NULL);
        if (cur && cur->type != TOKEN_WORD)
        {
            new->type = give_type(cur);
            new->cmd = ft_strdup("lower token"); // Handle token types separately
            go_to_next_job(job_list, new);
            cur = cur->next;
            continue;
        }
        cmd = full_cmd(&cur);
        new->cmd = ft_strdup(cmd);
        free(cmd);
        if (cur && cur->type == TOKEN_WORD)
            new->execd = get_execd(&cur);
        go_to_next_job(job_list, new);
    }
}
