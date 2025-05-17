/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 00:35:21 by bruno             #+#    #+#             */
/*   Updated: 2025/05/14 18:52:44 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_putchar(int c, int *len)
{
	write(1, &c, 1);
	(*len)++;
}

void	format(va_list args, const char format, int *len, t_flag *flags)
{
	if (format == 'd' || format == 'i')
		ft_putnbr(va_arg(args, int), len, flags);




	if (format == 'c')
		ft_putchar(va_arg(args, int), len);
	if (format == 's')
		ft_putstr(va_arg(args, char *), len);
	if (format == 'p')
		ft_pointer(va_arg(args, size_t), len);
	if (format == 'u')
		ft_uint(va_arg(args, unsigned int), len);
	if (format == 'x')
		ft_hexa(va_arg(args, unsigned int), 'x', len);
	if (format == 'X')
		ft_hexa(va_arg(args, unsigned int), 'X', len);
	if (format == '%')
		ft_putchar('%', len);
}

void	init_flags(t_flag *flags)
{
	flags->plus = false;
}

bool	isFlag(int c)
{
	if (c == '+')
		return (true);
	return (false);
}

void	set_flags(t_flag *flags, const char **str)
{
	while (**str && isFlag(**str)){
		if (**str == '+')
			flags->plus = true;
		(*str)++;
	}
}

int	ft_printf(const char *str, ...)
{
	int		len;
	int		i;
	va_list	args;
	t_flag	flags;

	init_flags(&flags);
	i = 0;
	len = 0;
	if (!str)
		return (-1);
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%'){
			set_flags(&flags, &str);
			format(args, str[i], &len, &flags);
		}
		else
			ft_putchar(str[i], &len);
		i++;
	}
	va_end(args);
	return (len);
}
