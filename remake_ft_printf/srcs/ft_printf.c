#include "../includes/ft_printf.h"
//len += ft_putchar(va_arg(args, int));


int	format(va_list args, char format)
{
	if (format == 'c')
		len += ft_putchar(va_arg(args, int));
	return (len);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int	len = 0, i = 0;

	while (str[i])
	{

		i++;
	}
	va_start(args, str);
	va_end(args);
}