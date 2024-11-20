/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 00:35:21 by bruno             #+#    #+#             */
/*   Updated: 2024/11/20 16:39:44 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(int c, int *len)
{
	write(1, &c, 1);
	(*len)++;
}

void	format(va_list args, const char format, int *len)
{
	if (format == 'c')
		ft_putchar(va_arg(args, int), len);
	if (format == 's')
		ft_putstr(va_arg(args, char *), len);
	if (format == 'd' || format == 'i')
		ft_putnbr(va_arg(args, int), len);
	if (format == 'u')
		ft_unsigned_int(va_arg(args, unsigned int), len);
	if (format == 'p')
		ft_pointer(va_arg(args, size_t), "0123456789abcdef", len);
	if (format == 'x')
		ft_hexa(va_arg(args, unsigned int), "0123456789abcdef", len);
	if (format == 'X')
		ft_hexa(va_arg(args, unsigned int), "0123456789ABCDEF", len);
	if (format == '%')
		ft_putchar('%', len);
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
				format(args, str[i++ + 1], &len);
		}
		else
			ft_putchar(str[i], &len);
	}
	va_end(args);
	return (len);
}
/*
int	main(void)
{
	printf("%d\n", ft_printf("attempt %%%&arguments\n\n"));
	printf("%d\n", printf("attempt %%%&arguments\n\n"));
}*/
