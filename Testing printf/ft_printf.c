/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 18:15:03 by brfernan          #+#    #+#             */
/*   Updated: 2024/01/03 17:42:31 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	format(char format, va_list args)
{
	int	len;

	len = 0;
	if (format == 'c')
		len += ft_putchar(va_arg(args, int));
	if (format == 's')
		len += ft_putstr(va_arg(args, char *));
	if (format == 'x')
		len += ft_hexa(va_arg(args, size_t), 'x', len);
	if (format == 'X')
		len += ft_hexa(va_arg(args, size_t), 'X', len);
	if (format == 'p')
		len += ft_hexa(va_arg(args, size_t), 'p', len);
	if (format == 'i' || format == 'd')
		len += ft_putnbr(va_arg(args, int), len);
	if (format == 'u')
		len += ft_putunsnbr(va_arg(args, int), len);
	if (format == '%')
		len += ft_putchar('%');
	return (len);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		len;

	i = 0;
	len = 0;
	if (!str)
		return (-1);
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			len += format(str[i + 1], args);
			i++;
		}
		else
			len += ft_putchar(str[i]);
		i++;
	}
	va_end(args);
	return (len);
}

/*int main(void)
{
	int hexa1= 50;
	int hexa2 = 500;
	int hi = 10;
	void *ptr = &hi;
	printf("\nftprintf = %d\n", ft_printf("%c%s%u%d%i%c%x%X%p%%", 'h', "ello ", 100, 42, 6969, ' ', hexa1, hexa2, ptr));
	printf("\nprintf = %d",        printf("%c%s%u%d%i%c%x%X%p%%", 'h', "ello ", 100, 42, 6969, ' ', hexa1, hexa2, ptr));
	
}*/
