/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ytree.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 18:20:43 by ycantin           #+#    #+#             */
/*   Updated: 2024/07/11 03:35:05 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* t_ast   *parse_leaf(t_token **token)
{
    if ((*token) == NULL || (*token)->type != TOKEN_WORD)
        return (NULL);
    t_ast *new;

    new = ast_new_node((*token)->type, (*token)->token);
    *token = (*token)->next;
    return (new);
}

t_ast   *parse_pipe(t_token **token)
{
    t_ast *left;
    t_ast *curr;

    left = parse_leaf(token);
    while ((*token)->type == TOKEN_PIPE && token != NULL)
    {
        curr = ast_new_node((*token)->type, NULL);
        curr->left = left;
        *token = (*token)->next;
        curr->right = parse_leaf(token);
        left = curr;
    }
    return (left);
}

t_ast   *parse_and_or(t_token **token)
{
    t_ast *left;
    t_ast *curr;

    left = parse_pipe(token);
    while (((*token)->type == TOKEN_OR || (*token)->type == TOKEN_AND) && token != NULL)
    {
        curr = ast_new_node((*token)->type, NULL);
        curr->left = left;
        *token = (*token)->next;
        curr->right = parse_pipe(token);
        left = curr;
    }
    return (left);
}

t_ast   *create_tree(t_token **token)
{
    t_token **currenttoken;
    
    currenttoken = token;
    return (parse_and_or(currenttoken));
}
 */

/* t_token *parse_cmd(t_token *cmd)
{

}

t_token *parse_exec(t_token *cur)
{
    if (cur->prev->type == TOKEN_REDIR)
        parse_redir(cur);
    //execution ft that takes the next node as th word to exec;
    return (cur);
}

t_token *parse_redir(t_token *cur)
{
    return (cur);
}

t_token *parse_pipe(t_token *cur)
{
    ;

    cur = parse_exec(cur->token);
    if (cur->next->type == TOKEN_PIPE)
    {
        cur = /* pipe_cmd BRUNO INSERTS HIS FT HERE*/(cur, parse_pipe(cur->next->next));
    }
    return (cur);
}

t_token *parse_parentheses(t_token *cur)
{
    return (cur);
}

t_token *parse_AND_OR(t_token *cur)
{
    return (cur);
} */