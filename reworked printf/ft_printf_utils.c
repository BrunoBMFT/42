/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 17:33:57 by bruno             #+#    #+#             */
/*   Updated: 2024/01/19 15:40:24 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *str)
{
	int	i;

	if (!str)
		return (ft_putstr("(null)"));
	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
	return (i);
}

int	ft_hexa(size_t x, char xXp, int len)
{
	char	str[25];
	char	*base;
	int		i;

	if (xXp == 'X')
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	i = 0;
	if (x == 0) // if (x == 0 && !isPtr) isPtr to check if it is pointer, since pointer null is nil and not 0
		return (ft_putstr("0"));
	if (!x)
		return (ft_putstr("(nil)"));
	if (xXp == 'p')
		len += write(1, "0x", 2);
	while (x != 0)
	{
		str[i] = base [x % 16];
		x = x / 16;
		i++;
	}
	while (i--)
		len += ft_putchar(str[i]);
	return (len);
}

int	ft_putnbr(int n, int len)
{
	if (n == -2147483648)
		return (write(1, "-2147483648", 11));
	if (n < 0)
	{
		len += ft_putchar('-');
		n *= -1;
	}
	if (n >= 10)
	{
		len += ft_putnbr(n / 10, len);
		n = n % 10;
	}
	if (n < 10)
		len += ft_putchar(n + '0');
	return (len);
}

int	ft_putunsnbr(unsigned int n, int len)
{
	if (n >= 10)
	{
		len += ft_putunsnbr(n / 10, len);
		n = n % 10;
	}
	if (n < 10)
		len += ft_putchar(n + '0');
	return (len);
}
