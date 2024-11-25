/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 00:35:21 by bruno             #+#    #+#             */
/*   Updated: 2024/11/20 16:57:39 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_putchar(int c, int fd, int *len)
{
	write(fd, &c, 1);
	(*len)++;
}

void	format(va_list args, const char format, int fd, int *len)
{
	if (format == 'c')
		pf_putchar(va_arg(args, int), fd, len);
	if (format == 's')
		pf_putstr(va_arg(args, char *), fd, len);
	if (format == 'd' || format == 'i')
		pf_putnbr(va_arg(args, int), fd, len);
	if (format == 'u')
		pf_unsigned_int(va_arg(args, unsigned int), fd, len);
	if (format == 'p')
		pf_pointer(va_arg(args, size_t), fd, len);
	if (format == 'x')
		pf_hexa(va_arg(args, unsigned int), "0123456789abcdef", fd, len);
	if (format == 'X')
		pf_hexa(va_arg(args, unsigned int), "0123456789ABCDEF", fd, len);
	if (format == '%')
		pf_putchar('%', fd, len);
}

static int	is_possible(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_printf(const char *str, ...)
{
	int		len;
	int		i;
	va_list	args;

	i = -1;
	len = 0;
	if (!str)
		return (-1);
	va_start(args, str);
	while (str[++i])
	{
		if (str[i] == '%')
		{
			while (!is_possible(POSSIBLE, str[i + 1]))
				i++;
			if (is_possible(POSSIBLE, str[i + 1]))
				format(args, str[i++ + 1], 1, &len);
		}
		else
			pf_putchar(str[i], 1, &len);
	}
	va_end(args);
	return (len);
}

int	ft_printf_fd(int fd, const char *str, ...)
{
	int		len;
	int		i;
	va_list	args;

	i = -1;
	len = 0;
	if (!str)
		return (-1);
	va_start(args, str);
	while (str[++i])
	{
		if (str[i] == '%')
		{
			while (!is_possible(POSSIBLE, str[i + 1]))
				i++;
			if (is_possible(POSSIBLE, str[i + 1]))
				format(args, str[i++ + 1], fd, &len);
		}
		else
			pf_putchar(str[i], fd, &len);
	}
	va_end(args);
	return (len);
}
