#ifndef FIRST_H
# define FIRST_H

# include <unistd.h>
# include <stdio.h>

void	ft_putstr(char *str);

# ifndef myPutstr
#  define myPutstr ft_putstr
# endif

#endif