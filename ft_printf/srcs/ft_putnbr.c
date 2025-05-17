/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 00:04:49 by bruno             #+#    #+#             */
/*   Updated: 2025/05/14 18:45:09 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_putnbr(int n, int *len, t_flag *flags)
{
	if (n == -2147483648)
		return (ft_putstr("-2147483648", len));
	if (n < 0)
	{
		ft_putchar('-', len);
		n *= -1;
	}
	else if (flags->plus)//can only run on the first time
	{
		ft_putchar('+', len);
	}
	if (n >= 10)
	{
		ft_putnbr(n / 10, len, flags);
		n %= 10;
	}
	ft_putchar(n + '0', len);
}