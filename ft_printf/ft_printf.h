/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:39:19 by bruno             #+#    #+#             */
/*   Updated: 2023/11/03 16:03:17 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int	ft_putchar(int c);
int	format(va_list args, const char format);
int	ft_printf(const char *str, ...);
int	ft_putstr(char *str);
int	ft_putnbr(int n);
int	putnbr_len(int n);
int	ft_unsigned_int(unsigned int u);
int	unsigned_len(unsigned int num);
int	ft_pointer(size_t pointer);
int	ft_hexa(unsigned int x, char x_or_x);
#endif