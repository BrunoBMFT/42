/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:39:19 by bruno             #+#    #+#             */
/*   Updated: 2025/05/14 18:43:03 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdbool.h>

typedef struct	s_flag
{
	bool		plus;
}				t_flag;


int	ft_printf(const char *str, ...);





void	ft_putnbr(int n, int *len, t_flag *flags);

void	ft_putchar(int c, int *len);
void	ft_putstr(char *str, int *len);
void	ft_uint(unsigned int u, int *len);
void	ft_hexa(unsigned int x, char x_or_x, int *len);
void	ft_pointer(size_t pointer, int *len);


#endif