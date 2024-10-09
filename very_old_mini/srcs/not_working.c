
//expand $USER$USER


// make sure export creates the variable second to last, before _=usr/bin/env
void	caught_export(char *input, char **env)
{
	
}


void	caught_unset(char *input, char **env)
{
	int		i;
	int		j;
	char	*to_remove;
	char	*var;
	char	**new_env;

	var = ft_strrem(input, "unset ");
	new_env = ft_calloc(sizeof(char *), ft_split_wordcount(env) - 1);
	i = 0;
	while (env[i] && ft_strnstr(env[i], var, ft_strlen(var)) == 0)
		i++;
	if (!env[i])
		return ((void)NULL);
	to_remove = env[i];
	i = 0;
	j = 0;
	while (env[i])//move with pointer
	{
		if (ft_strnstr(env[i], to_remove, ft_strlen(to_remove)) == 0)
		{
			new_env[j] = env[i];
			j++;
		}
		else
		{
			i++;
		}
	}
	env = new_env;
}