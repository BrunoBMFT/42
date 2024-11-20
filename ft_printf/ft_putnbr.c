/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:27:53 by bruno             #+#    #+#             */
/*   Updated: 2024/11/20 16:23:20 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr(int n, int *len)
{
	char	c;

	if (n == -2147483648)
		return (ft_putstr("-2147483648", len));
	if (n < 0)
	{
		ft_putchar('-', len);
		n *= -1;
	}
	if (n >= 10)
	{
		ft_putnbr(n / 10, len);
		n %= 10;
	}
	c = '0' + n;
	ft_putchar(c, len);
}

void	ft_unsigned_int(unsigned int u, int *len)
{
	if (u == 0)
		return (ft_putchar('0', len));
	if (u >= 10)
		ft_unsigned_int(u / 10, len);
	ft_putchar(u % 10 + '0', len);
}
