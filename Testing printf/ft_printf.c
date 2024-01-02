/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 18:15:03 by brfernan          #+#    #+#             */
/*   Updated: 2024/01/02 23:56:52 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

int	ft_putchar(int c)
{
	return (write(1, &c, 1));
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
	if (x == 0)
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

int	ft_putnbr(int n)
{
	int len;

	len = 0;
	if (n == -2147483648)
		return (write(1, "-2147483648", 11));
	if (n < 0)
	{
		len += ft_putchar('-');
		n *= -1;
	}
	if (n >= 10)
	{
		len += ft_putnbr(n / 10);
		n = n % 10;
	}
	if (n < 10)
		len += ft_putchar(n + '0');
	return (len);
}

int	ft_putunsnbr(unsigned int n)
{
	int len;

	len = 0;
	if (n >= 10)
	{
		len += ft_putunsnbr(n / 10);
		n = n % 10;
	}
	if (n < 10)
		len += ft_putchar(n + '0');
	return (len);
}


int	format(char format, va_list args)
{
	int	len; //use len from ft_printf and delete this one

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
		len += ft_putnbr(va_arg(args, int));
	if (format == 'u')
		len += ft_putunsnbr(va_arg(args, int));
	if (format == '%')
		len += ft_putchar('%');
	return (len);
}

int	ft_printf(const char *str, ...)
{
	va_list args;
	int		i;
	int		len;

	i = 0;
	len = 0;
	if (!str)
		return (-1);
	va_start(args, str);
	while(str[i])
	{
		if (str[i] == '%')
		{
			len += format(str[i + 1], args);
		}
		i++;
	}
	va_end(args);
	return (len);
}

int main(void)
{ // SOMETHING VERY WRONG

//	printf("\nftprintf = %d\n", ft_printf("%u", 100));
//	printf("\nprintf = %d\n", printf("%u", 100));
	int hexa1= 50;
	int hexa2 = 500;
	int hi = 10;
	void *ptr = &hi;
	printf("\nftprintf = %d\n", ft_printf("%c%s%u%d%i%c%x%X%p%%", 'h', "ello ", 100, 42, 6969, ' ', hexa1, hexa2, ptr));
	printf("\nprintf = %d",        printf("%c%s%u%d%i%c%x%X%p%%", 'h', "ello ", 100, 42, 6969, ' ', hexa1, hexa2, ptr));
	
}