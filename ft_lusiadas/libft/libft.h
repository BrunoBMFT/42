/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:25:50 by brfernan          #+#    #+#             */
/*   Updated: 2024/01/22 21:46:04 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

int	ft_printf(const char *str, ...);
int	ft_strlen_gnl(char *str);
char	*ft_strjoin_gnl(char *line, char *buf);
char	*clearbuf(char *buf);
char	*get_next_line(int fd);

#endif