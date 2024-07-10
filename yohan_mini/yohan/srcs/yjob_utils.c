/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yjob_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 18:20:43 by ycantin           #+#    #+#             */
/*   Updated: 2024/07/10 20:13:51 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int give_type(t_token *token)
{
    if(token->type == TOKEN_PIPE)
        return (TOKEN_PIPE);
    else if(token->type == TOKEN_AND)
        return (TOKEN_AND);
    else if(token->type == TOKEN_OR)
        return (TOKEN_OR);
    else if(token->type == TOKEN_REDIR)
        return (TOKEN_REDIR);
    return (0);
}

int count_jobs(t_token *tokens)
{
    int num;
    t_token *cur;

    num = 0;
    cur = tokens;
    while (cur)
    {
        if (cur->type == TOKEN_WORD)
        {
            cur = cur->next;
            while (cur && cur->token[0] == '-')      
                cur = cur->next;
            num++;
            if (!cur) 
                break;
        }
        if (cur && (cur->type == TOKEN_AND || cur->type == TOKEN_OR ||
                 cur->type == TOKEN_PIPE || cur->type == TOKEN_REDIR))
            num++;
        cur = cur->next;
    }
    return (num);
}

t_jobs	*addjob(void *content)
{
	t_jobs	*list;

	list = malloc(sizeof(t_jobs));
	if (!list)
		return (NULL);
	list->cmd = content;
    list->execd = NULL;
	list->next = NULL;
	return (list);
}

t_jobs	*get_last_job(t_jobs *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	go_to_next_job(t_jobs **lst, t_jobs *new)
{
	t_jobs	*current;

	if (!new)
		return ;
	current = get_last_job(*lst);
	if (lst && current)
		current->next = new;
	else
		*lst = new;
}
