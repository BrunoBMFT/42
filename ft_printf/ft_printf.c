/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 00:35:21 by bruno             #+#    #+#             */
/*   Updated: 2023/11/03 16:27:41 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	format(va_list args, const char format)
{
	int		len;

	len = 0;
	if (format == 'c')
		len += ft_putchar(va_arg(args, int));
	if (format == 's')
		len += ft_putstr(va_arg(args, char *));
	if (format == 'p')
		len += ft_pointer(va_arg(args, size_t));
	if (format == 'd' || format == 'i')
		len += ft_putnbr(va_arg(args, int));
	if (format == 'u')
		len += ft_unsigned_int(va_arg(args, unsigned int));
	if (format == 'x')
		len += ft_hexa(va_arg(args, unsigned int), 'x');
	if (format == 'X')
		len += ft_hexa(va_arg(args, unsigned int), 'X');
	if (format == '%')
		len += ft_putchar('%');
	return (len);
}

int	ft_printf(const char *str, ...)
{
	int		len;
	int		i;
	va_list	args;

	i = 0;
	len = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			len += format(args, str[i + 1]);
			i++;
		}
		else
		{
			len += ft_putchar(str[i]);
		}
		i++;
	}
	va_end(args);
	return (len);
}
