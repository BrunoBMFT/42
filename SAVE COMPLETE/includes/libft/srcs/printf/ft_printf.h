/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:25:50 by brfernan          #+#    #+#             */
/*   Updated: 2024/12/20 02:20:53 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define POSSIBLE_PF "cspdiuxX%"
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>

int		ft_printf(const char *str, ...);
int		ft_printf_fd(int fd, const char *str, ...);
void	pf_putchar(int c, int fd, int *len);
void	pf_putstr(char *str, int fd, int *len);
void	pf_putnbr(int n, int fd, int *len);
void	pf_unsigned_int(unsigned int u, int fd, int *len);
void	pf_pointer(size_t pointer, int fd, int *len);
void	pf_hexa(unsigned int x, char *base, int fd, int *len);

#endif
