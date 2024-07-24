/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 03:18:24 by bruno             #+#    #+#             */
/*   Updated: 2024/07/24 03:59:38 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*expand_env_vars(char *input, char **env, char **temp_vars)
{
	int 	i;
	bool	flag = false;
	char	**vars = ft_split(input, '$');//error check
	char	*output = NULL;
	char	*temp = NULL;

	if (input[0] != '$')
		flag = true;
	i = 0;
	while (vars[i])
	{
		if (flag)
			flag = false;// dont hardcode like this
		else
		{
			temp = ft_getenv(vars[i], env);
			if (!temp)
				temp = ft_getenv(vars[i], temp_vars);
			vars[i] = temp;
		}
		if (vars[i])
		{
			if (!output)
				output = ft_strdup(vars[i]);//error check
			else
				output = ft_strjoin(output, vars[i]);//error check
		}
		i++;
	}
	//free
	if (input[ft_strlen(input) - 1] == '$')//! dont hardcode like this
		ft_strcat(output, "$");
	output[ft_strlen(output)] = 0;
	return (output);
}

//Variable names in the shell should consist of alphanumeric characters and underscores (_). They should not start with a digit.
//job.job divides strings into cmd and execd strings. basically for this function to work, job_list has to be different
char	**variable_declaration(char **str, char **vars)//will work with expand_vars
{
	char **temp_vars;
	int		var_count = ft_split_wordcount(vars);
	int		str_count = ft_split_wordcount(str);
	temp_vars = ft_calloc(sizeof(char *), var_count + str_count + 1);
	if (!temp_vars)
		panic("malloc\n");
	int i = 0;
	while (i < var_count)
	{
        bool found = false;
		int j = 0;
		while (j < str_count)
        {
            if (ft_strncmp(vars[i], str[j], len_to_equal(vars[i])) == 0) 
			{
                temp_vars[i] = ft_strdup(str[j]);
                found = true;
                break;
            }
			j++;
        }
        if (found == false)
            temp_vars[i] = ft_strdup(vars[i]);
		i++;
    }
	int j = 0;
	while (j < str_count)
	{
        bool found = false;
		int k = 0;
		while (k < var_count)
        {
            if (ft_strncmp(str[j], vars[k], len_to_equal(vars[k])) == 0) 
			{
                found = true;
                break;
            }
			k++;
        }
        if (found == false)
            temp_vars[i++] = ft_strdup(str[j]);
		j++;
    }
//	temp_vars[var_count + str_count] = NULL;
/* 	i = 0;
	while (temp_vars[i])
	{
		printf("%d: %s\n", i, temp_vars[i]);
		i++;
	} */
	return (temp_vars);
}

