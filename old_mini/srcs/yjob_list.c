/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yjob_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 18:20:43 by ycantin           #+#    #+#             */
/*   Updated: 2024/07/11 03:38:01 by bruno            ###   ########.fr       */
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

char **job_array(t_jobs *node)
{
    char **array;
    char **new_array;
    int i;
    
    array = ft_split(node->cmd, ' ');
    i = count_strings(array);
    new_array = malloc(sizeof(char *) * (i + 2));
    if (!new_array)
    {
        free(array);
        return(NULL);
    }
    i = 0;
    while (array[i])
    {
        new_array[i] = ft_strdup(array[i]);
        i++;
    }
    new_array[i] = ft_strdup(node->execd);
    new_array[i + 1] = NULL;
    ft_free_array(array);
    return (new_array);
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
            new->cmd = ft_strdup("token"); // Handle token types separately
            go_to_next_job(job_list, new);
            cur = cur->next;
            continue;
        }
        //new->job = job_array(cur);
        
        cmd = full_cmd(&cur);
        new->cmd = ft_strdup(cmd);
        free(cmd);
        if (cur && cur->type == TOKEN_WORD)
            new->execd = get_execd(&cur);
        if (new->cmd && new->execd)
            new->job = job_array(new);
        else
            new->job = NULL;
        go_to_next_job(job_list, new);
    }
}
