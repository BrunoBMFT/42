#include "../includes/minishell.h"

bool	unclosed_quotes(char *input)
{
	int i = 0;
	int single_count = 0;
	bool	single_opened = false;
	int double_count = 0;
	bool	double_opened = false;
	while (input[i])
	{
		if (input[i] == '\'' && !single_opened){
			single_opened = true;
			single_count++;
			i++;
			continue;
		}
		if (input[i] == '\'' && single_opened){
			single_opened = false;
			single_count--;
			i++;
			continue;
		}
		//do double quotes now
		i++;
	}
	if (single_opened || double_opened){
		printf("unclosed quote\n");
		return (true);
	}
	return (false);
}

void	quotes(t_info *info)
{
	if (unclosed_quotes(info->input))
		return ;
}

int	main(void)
{
	t_info info;

	while (1)
	{
		info.input = readline("$>");
		if (!info.input)
			break ;
		testing(info);
		quotes(&info);


		
	}
}