/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 00:04:49 by bruno             #+#    #+#             */
/*   Updated: 2024/11/20 16:36:46 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

void	ft_pointer(size_t pointer, char *base, int *len)
{
	char	str[25];
	int		i;

	if (!pointer)
		return (ft_putstr("(nil)", len));
	i = 0;
	ft_putstr("0x", len);
	while (pointer != 0)
	{
		str[i] = base[pointer % 16];
		pointer = pointer / 16;
		i++;
	}
	while (i--)
		ft_putchar(str[i], len);
}

void	ft_hexa(unsigned int n, char *base, int *len)
{
	if (n == 0)
		return (ft_putchar('0', len));
	if (n >= 16)
		ft_hexa(n / 16, base, len);
	ft_putchar(base[n % 16], len);
}
