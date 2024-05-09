#include "../includes/ft_printf.h"

int	main(void)
{
	char *str = "hello";
	printf("%d", ft_printf(str));
	printf("%d", printf(str));
}