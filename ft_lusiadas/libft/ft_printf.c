# include <unistd.h>
# include <stdarg.h>

int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *str, int len)
{
	int	i = 0;
	if (!str)
		return (ft_putstr("(null)", len));
	while (str[i])
	{
		len += ft_putchar(str[i]);
		i++;
	}
	return (i);
}
int	format(va_list args, const char format, int len)
{
	if (format == 's')
		len += ft_putstr(va_arg(args, char *), len);
	return (len);
}

int	ft_printf(const char *str, ...)
{
	int		len = 0, i = -1;
	va_list	args;
	if (!str)
		return (-1);
	va_start(args, str);
	while (str[++i])
	{
		if (str[i] == '%')
		{
			len += format(args, str[i++ + 1], len);
		}
		else
			len += ft_putchar(str[i]);
	}
	va_end(args);
	return (len);
}
