/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 00:35:21 by bruno             #+#    #+#             */
/*   Updated: 2024/03/30 17:59:41 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_putchar(int c)
{
	write(1, &c, 1);
}

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
	write(1, "\n", 1);
	return (i);
}

void	ft_putnbr(int n)
{
	char	c;

	if (n < 0)
	{
		write(1, "-", 1);
		n *= -1;
	}
	if (n >= 10)
	{
		ft_putnbr(n / 10);
		n = n % 10;
	}
	if (n < 10)
	{
		c = '0' + n;
		write(1, &c, 1);
	}
}

void	format(va_list args, const char format)
{
	if (format == 's')
		ft_putstr(va_arg(args, char *));
	if (format == 'd' || format == 'i')
		ft_putnbr(va_arg(args, int));
	if (format == '%')
		ft_putchar('%');
}

int	ft_printf(const char *str, ...)
{
	int		i;
	va_list	args;

	i = -1;
	va_start(args, str);
	while (str[++i])
	{
		if (str[i] == '%')
			format(args, str[i++ + 1]);
		else
			ft_putchar(str[i]);
	}
	va_end(args);
	return (1);
}
