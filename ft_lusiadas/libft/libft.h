#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <fcntl.h>

int	ft_printf(const char *str, ...);
int	ft_strlen_gnl(char *str);
char	*ft_strjoin_gnl(char *line, char *buf);
char	*clearbuf(char *buf);
char	*get_next_line(int fd);

#endif