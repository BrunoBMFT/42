/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 00:04:49 by bruno             #+#    #+#             */
/*   Updated: 2023/11/03 16:27:45 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_putstr(char *str, int *len)
{
	int	i;

	if (!str)
		return (ft_putstr("(null)", len));
	i = 0;
	while (str[i])
	{
		ft_putchar(str[i], len);
		i++;
	}
}

void	ft_pointer(size_t pointer, int *len)
{
	char	str[25];
	int		i;
	char	*base;

	if (!pointer)
		return (ft_putstr("(nil)", len), (void)NULL);
	base = "0123456789abcdef";
	i = 0;
	write(1, "0x", 2);
	while (pointer)
	{
		str[i] = base[pointer % 16];
		pointer = pointer / 16;
		i++;
	}
	*len += 2;
	while (i--)
		ft_putchar(str[i], len);
}

void	ft_hexa(unsigned int x, char x_or_x, int *len)
{
	char	str[25];
	char	*base;
	int		i;

	if (x_or_x == 'X')
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	i = 0;
	if (x == 0)
		return (ft_putchar('0', len), (void)NULL);
	while (x)
	{
		str[i] = base [x % 16];
		x = x / 16;
		i++;
	}
	while (i--)
		ft_putchar(str[i], len);
}

void	ft_uint(unsigned int u, int *len)
{
	if (u >= 10)
	{
		ft_uint(u / 10, len);
		u %= 10;
	}
	ft_putchar(u + '0', len);
}
