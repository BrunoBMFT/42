#include "../includes/minishell.h"

void separator(){
	printf("============================\n");
}

void	testing(t_info info)
{
	separator();
	printf("Input:\n");
	printf("%s\n", info.input);
	separator();
}
