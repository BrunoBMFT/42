/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:27:53 by bruno             #+#    #+#             */
/*   Updated: 2023/11/03 16:27:33 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int n)
{
	char	c;
	int		len;

	len = putnbr_len(n);
	if (n == -2147483648)
	{
		return (ft_putstr("-2147483648"));
	}
	if (n < 0)
	{
		len += ft_putstr("-");
		n *= -1;
	}
	if (n >= 10)
	{
		ft_putnbr(n / 10);
		n %= 10;
	}
	if (n < 10)
	{
		c = '0' + n;
		write(1, &c, 1);
	}
	return (len);
}

int	putnbr_len(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n >= 1 || n <= -1)
	{
		len++;
		n /= 10;
	}
	return (len);
}

int	ft_unsigned_int(unsigned int u)
{
	int	len;

	if (u == 0)
		return (ft_putstr("0"));
	len = unsigned_len(u);
	if (u >= 10)
	{
		ft_unsigned_int(u / 10);
	}
	ft_putchar(u % 10 + '0');
	return (len);
}

int	unsigned_len(unsigned int num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		len++;
		num = num / 10;
	}
	return (len);
}
