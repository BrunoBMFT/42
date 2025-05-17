/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 00:04:49 by brfernan          #+#    #+#             */
/*   Updated: 2024/12/16 04:08:38 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_putnbr(int n, int fd, int *len)
{
	if (n == -2147483648)
		return (pf_putstr("-2147483648", fd, len));
	if (n < 0)
	{
		pf_putchar('-', fd, len);
		n *= -1;
	}
	if (n >= 10)
	{
		pf_putnbr(n / 10, fd, len);
		n %= 10;
	}
	pf_putchar((n % 10 + '0'), fd, len);
}

void	pf_unsigned_int(unsigned int n, int fd, int *len)
{
	if (n == 0)
		return (pf_putstr("0", fd, len));
	if (n >= 10)
		pf_unsigned_int(n / 10, fd, len);
	pf_putchar(n % 10 + '0', fd, len);
}

void	pf_putstr(char *str, int fd, int *len)
{
	int	i;

	if (!str)
		return (pf_putstr("(null)", fd, len));
	i = 0;
	while (str[i])
	{
		pf_putchar(str[i], fd, len);
		i++;
	}
}

void	pf_pointer(size_t pointer, int fd, int *len)
{
	char	str[25];
	int		i;
	char	*base;

	if (!pointer)
		return (pf_putstr("(nil)", fd, len));
	i = 0;
	pf_putstr("0x", fd, len);
	base = "0123456789abcdef";
	while (pointer != 0)
	{
		str[i] = base[pointer % 16];
		pointer = pointer / 16;
		i++;
	}
	while (i--)
		pf_putchar(str[i], fd, len);
}

void	pf_hexa(unsigned int n, char *base, int fd, int *len)
{
	if (n == 0)
		return (pf_putchar('0', fd, len));
	if (n >= 16)
		pf_hexa(n / 16, base, fd, len);
	pf_putchar(base[n % 16], fd, len);
}
