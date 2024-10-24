/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   heredoc.c										  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: ycantin <ycantin@student.42.fr>			+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/06/26 18:20:43 by ycantin		   #+#	#+#			 */
/*   Updated: 2024/08/29 18:59:07 by ycantin		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../includes/minishell.h"


char	*no_quotes_hd(char *str, t_var_holder *h, t_env *env, int **expand_flag)
{
	h->temp = ft_strndup(str + h->start, h->i - h->start);
	if (!h->temp)
		return (h->new);
	h->before = expand(h->temp, env);
	free(h->temp);
	if (!h->before)
		return (h->new);
	if (!h->new)
		h->new = ft_strdup(h->before);//this is leaked in export????
	else
	{
		h->temp = ft_strjoin(h->new, h->before);
		free(h->new);
		h->new = h->temp;
	}
	**expand_flag = 1;
	free(h->before);
	if (!h->new)
		return (NULL);
	return (h->new);
}

char	*single_quotes_hd(char *str, t_var_holder *h, char quote, int **expand_flag)
{
	if (!h->new)
		h->new = ft_strdup("");
	h->start = ++h->i;
	while (str[h->i] && str[h->i] != quote)
		h->i++;
	h->quoted = ft_strndup(str + h->start, h->i - h->start);
	if (!h->quoted)
		return h->new;
	h->temp = ft_strdup(h->new);
	free(h->new);
	h->new = ft_strjoin(h->temp, h->quoted);
	free(h->quoted);
	free(h->temp);
	**expand_flag = 0;
	if (!h->new)
		return (NULL);
	return (h->new);
}

void	heredoc_expand_check(int *expand_flag, t_jobs **job, t_env env)
{
	// char *temp;

	// if ((*job)->delimiters[0] == '\'' || (*job)->delimiters[0] == '\"')
	// {
	// 	temp = ft_substr((*job)->delimiters, 1, (ft_strlen((*job)->delimiters) - 2));
	// 	free((*job)->delimiters);
	// 	(*job)->delimiters = temp;
	// 	*expand_flag = 0;
	// }
	char *str = (*job)->delimiters;
	t_var_holder h;

	h.new = NULL;
	h.before = NULL;
	h.quoted = NULL;
	h.after = NULL;
	h.temp = NULL;
	h.i = 0;
	h.start = 0;
	if (is_empty_arg(str, '\'') || is_empty_arg(str, '\"'))
		h.new = ft_strdup("");
	while (str[h.i])
	{
		h.start = h.i;
		while (str[h.i] && str[h.i] != '\'' && str[h.i] != '\"')
			h.i++;
		if (h.i > h.start)
			h.new = no_quotes_hd(str, &h, &env, &expand_flag);
		if (str[h.i] == '\'' || str[h.i] == '\"')
			h.new = single_quotes_hd(str, &h, str[h.i], &expand_flag);
		if (str[h.i])
			h.i++;
	}
	free(str);
	(*job)->delimiters = h.new;
}

int	handle_heredoc(t_jobs *job, t_env env)
{
	int		redirected_input;
	char	*line;
	char	**delimiters;
	int		i;
	int		must_expand;
	int		max;

	i = 0;
	must_expand = 1;
	max = 0;
	redirected_input = open(job->heredoc_file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (redirected_input < 0)
		return (-1);
//	signal(SIGINT, handle_signal_heredoc);
//	signal(SIGQUIT, SIG_IGN);
	choose_signal(HEREDOC_SIG);
	choose_signal(IGNORE_SIG);
	//heredoc_expand_check(&must_expand, &job, env);
	heredoc_expand_check(&must_expand, &job, env);
	printf("%s	%d\n", job->delimiters, must_expand);
	while (1)
	{
		line = readline("heredoc>");
		if (!line || ft_strcmp(line, job->delimiters) == 0)
		{
			free(line);
			break ;
		}
		if (must_expand)
		{
			char *temp = expand(line, &env);
			// if (ft_strcmp(line, temp) == 0)
			// {
			// 	free(line);
			// 	break ;
			// }
			ft_putendl_fd(temp, redirected_input);
			free(temp);

		}
		else	
			ft_putendl_fd(line, redirected_input);
		free(line);
	}
	close(redirected_input);
	return (0);
}


// int	handle_heredoc(t_jobs *job)
// {
// 	int		redirected_input;
// 	char	*line;
// 	char	**delimiters;
// 	int		i;
// 	int		max;
// 	i = 0;
// 	max = 0;
// 	delimiters = ft_split(job->delimiters, ' ');
// 	while (delimiters[max])
// 		max++;
// 	redirected_input = open(".heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
// 	if (redirected_input < 0)
// 		return (-1);
// 	signal(SIGINT, handle_signal_heredoc);
// 	signal(SIGQUIT, SIG_IGN);
// 	while (i < (max - 1))
// 	{
// 		while (1)
// 		{
// 			line = readline("fake heredoc>");
// 			if (!line || ft_strcmp(line, delimiters[i]) == 0)
// 			{
// 				free(line);
// 				break ;
// 			}
// 			free(line);
// 		}
// 		i++;
// 	}
// 	while (1)
// 	{
// 		line = readline("heredoc>");
// 		if (!line || ft_strcmp(line, delimiters[i]) == 0)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		ft_putendl_fd(line, redirected_input);
// 		free(line);
// 	}
// 	close(redirected_input);
// 	free_array(delimiters);
// 	/* if (manage_redirection(job) < 0)
// 		return (-1); */
// 	return (0);
// }