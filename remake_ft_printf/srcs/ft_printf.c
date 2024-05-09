/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 23:08:15 by bruno             #+#    #+#             */
/*   Updated: 2024/05/09 23:25:51 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_putnum(int n, int len)
{
	if (n == INT_MIN)
		ft_putstr("-2147483648");
	if (n == 0)
		return (ft_putchar('0'));
	if (n < 0)
	{
		len += ft_putchar('-');
		n *= -1;
	}
	if (n >= 10)
	{
		len += ft_putnum((n / 10), len);
		n %= 10;
	}
	if (n < 10)
		len += ft_putchar(n + '0');
	return (len);
}

int	ft_putunsignnum(unsigned int n, int len)//fix len
{
	if (n == 0)
		return (ft_putchar('0'));
	if (n >= 10)
	{
		len += ft_putnum((n / 10), len);
		n %= 10;
	}
	if (n < 10)
		len += ft_putchar(n + '0');
	return (len);
}

int	ft_hexa(unsigned int n, char format, int len)
{
	char	*hex;
	char	write[10];
	int		i;

	i = 0;
	if (!n)
		return (ft_putstr("0"));
	if (format == 'X')
		hex = "0123456789ABCDEF";
	else
		hex = "0123456789abcdef";
	while (n)
	{
		write[i] = hex[n % 16];
		n /= 16;
		i++;
	}
	while (i--)
		len += ft_putchar(write[i]);
	return (len);
}

int	ft_ptr(size_t n, int len)
{
	char	write[10];
	char	*hex;
	int		i;

	if (!n)
		return (ft_putstr("(nil)"));
	i = 0;
	hex = "0123456789abcdef";
	len += ft_putstr("0x");
	while (n)
	{
		write[i] = hex[n % 16];
		n /= 16;
		i++;
	}
	while (i--)
		len += ft_putchar(write[i]);
	return (len);
}

int	format(va_list args, char format)
{
	int	len;

	len = 0;
	if (format == 'c')
		len += ft_putchar(va_arg(args, int));
	if (format == 's')
		len += ft_putstr(va_arg(args, char *));
	if (format == 'd' || format == 'i')
		len += ft_putnum(va_arg(args, int), 0);
	if (format == 'u')
		len += ft_putunsignnum(va_arg(args, unsigned int), 0);
	if (format == 'x' || format == 'X')
		len += ft_hexa(va_arg(args, size_t), format, 0);
	if (format == 'p')
		len += ft_ptr(va_arg(args, size_t), 0);
	if (format == '%')
		len += ft_putchar('%');
	return (len);
}

bool	is_in_string(char c, char *possible)//check if in libft
{
	int	i;

	i = 0;
	while (possible)
	{
		if (c == possible[i])
			return (true);
		i++;
	}
	return (false);
}

int	ft_printf(const char *str, ...)
{
	int		len;
	int		i;
	va_list	args;

	len = 0;
	i = 0;
	if (!str)
		return (-1);
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%' && is_in_string(str[i + 1], "cspdiuxX%"))
			len += format(args, str[i++ + 1]);
		else
			len += ft_putchar(str[i]);
		i++;
	}
	va_end(args);
	return (len);
}
