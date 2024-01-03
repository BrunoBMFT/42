/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 17:14:09 by bruno             #+#    #+#             */
/*   Updated: 2024/01/03 17:16:29 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>

int	ft_printf(const char *str, ...);
int	format(char format, va_list args);
int	ft_putchar(int c);
int	ft_putstr(char *str);
int	ft_hexa(size_t x, char xXp, int len);
int	ft_putnbr(int n, int len);
int	ft_putunsnbr(unsigned int n, int len);
#endif