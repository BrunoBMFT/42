/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:25:50 by brfernan          #+#    #+#             */
/*   Updated: 2025/04/06 00:55:27 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
# define POSSIBLE "cspdiuxX%"
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int		ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
char	*ft_itoa(int n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *str, int c, size_t n);
char	**ft_split(const char *s, char c);
char	*ft_strchr(const char *str, int c);
char	*ft_strdup(char const*s1);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t n);
size_t	ft_strlen(const char *str);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *h, const char *x, size_t n);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(const char *s, unsigned int start, size_t len);
int		ft_tolower(int c);
int		ft_toupper(int c);
t_list	*ft_lstlast(t_list *lst);
int		ft_printf(const char *str, ...);
int		ft_printf_putchar(int c);
int		format(va_list args, const char format);
int		ft_printf_putstr(char *str);
int		ft_printf_putnbr(int n);
int		putnbr_len(int n);
int		ft_unsigned_int(unsigned int u);
int		unsigned_len(unsigned int num);
int		ft_pointer(size_t pointer);
int		ft_hexa(unsigned int x, char x_or_x);
char	*get_next_line(int fd);
char	*gnl_ft_strjoin(char *line, char *buf);
int		buffer(char	*buf);
char	*clearbuf(char *buf);
long	ft_atol(const char *str);
void	ft_putchar(char c);
void	ft_putendl(char *s);
void	ft_putnbr(int n);
void	ft_putstr(char *s);

#endif
