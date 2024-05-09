#include "includes/ft_printf.h"

int	main(void)
{
	int num = -42;
	printf("len: %d\n", ft_printf("my output: %d\n", num));
	printf("len: %d\n", printf("pf output: %d\n", num));

	
/* 	char *str = "hello";
	printf("len: %d\n", ft_printf("my output: %s\n", str));
	printf("len: %d\n", printf("pf output: %s\n", str)); */
/* 
	printf("len: %d\n", ft_printf("my output: %x\n", 42));
	printf("len: %d\n", printf("pf output: %x\n", 42)); */
	
/* 	printf("len: %d\n", ft_printf("my output: %u\n", 4222));
	printf("len: %d\n", printf("pf output: %u\n", 4222)); */
}