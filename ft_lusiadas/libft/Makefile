NAME = libft.a

SRCS = ft_printf.c ft_printf_functions.c ft_printf_putnbr.c \
get_next_line_bonus.c get_next_line_utils_bonus.c

OBJS = $(SRCS:.c=.o)

COMPRESS = ar rcs

CFLAGS = -Wall -Wextra -Werror

RM = rm -f
MV = mv

%.o: %.c
	$(CC) -c $(CFLAGS) $?

all: $(NAME)

$(NAME): $(OBJS)
	$(COMPRESS) $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME) ../$(NAME)

re:  fclean all

install: $(NAME)
	$(MV) $(NAME) ../

.PHONY: all, clean, fclean, re, install