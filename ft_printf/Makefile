NAME = libftprintf.a

SRCS = ft_printf.c ft_printf_functions.c ft_putnbr.c

OBJS = $(SRCS:.c=.o)

CC = cc

COMPRESS = ar rcs

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

%.o: %.c
	$(CC) -c $(CFLAGS) $?

all = $(NAME)

$(NAME): $(OBJS)
		$(COMPRESS) $(NAME) $(OBJS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
			@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
		$(RM) $(OBJS)

fclean:	clean
		$(RM) $(NAME)

re:	fclean all

.PHONY:		all clean fclean re

