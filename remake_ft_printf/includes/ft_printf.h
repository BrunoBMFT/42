/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 23:09:01 by bruno             #+#    #+#             */
/*   Updated: 2024/05/09 23:21:29 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include "libft/libft.h"

int		ft_printf(const char *str, ...);
int		ft_putnum(int n, int len);
int		ft_putunsignnum(unsigned int n, int len);
int		ft_hexa(unsigned int n, char format, int len);
int		ft_ptr(size_t n, int len);
int		format(va_list args, char format);
bool	is_in_string(char c, char *possible);
#endif