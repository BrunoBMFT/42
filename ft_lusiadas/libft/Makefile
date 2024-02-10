NAME = libft.a

SRCS = ft_printf.c get_next_line_bonus.c get_next_line_utils_bonus.c

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

%.o: %.c
	$(CC) -c $(CFLAGS) $?

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) ../$(NAME)

re:  fclean all

install: $(NAME) clean
	mv $(NAME) ../

.PHONY: all, clean, fclean, re, install