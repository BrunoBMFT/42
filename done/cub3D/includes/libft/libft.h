/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:25:50 by brfernan          #+#    #+#             */
/*   Updated: 2024/12/16 04:08:46 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include "srcs/printf/ft_printf.h"
# include "srcs/gnl/get_next_line.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

// is
bool	ft_is_even(int n);
bool	ft_isalnum(int c);
bool	ft_isalpha(int c);
bool	ft_isascii(int c);
bool	ft_isdigit(int c);
bool	ft_isprint(int c);

//list
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);

//mem
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *str, int c, size_t n);

//put
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar(char c);
void	ft_putendl(char *s);
void	ft_putnbr(int n);
void	ft_putstr(char *s);
int		ft_tolower(int c);
int		ft_toupper(int c);

//mall
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	free_array(char **array);
char	*ft_itoa(int n);
char	**ft_split(const char *s, char c);
int		ft_split_wordcount(char **split);
char	*ft_strdup(char const*s1);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin3(char const *s1, char const *s2, char const *s3);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(const char *s, unsigned int start, size_t len);

//str
int		ft_atoi(const char *str);
long	ft_atol(const char *str);
void	ft_strcat(char *dest, char *src);
char	*ft_strchr(const char *str, int c);
int		ft_strcmp(char *s1, char *s2);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t n);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *h, const char *x, size_t n);
char	*ft_strrchr(const char *s, int c);

//aux
int		ft_printf(const char *str, ...);
int		ft_printf_fd(int fd, const char *str, ...);
char	*get_next_line(int fd);
char	*get_next_line_bonus(int fd);

#endif
