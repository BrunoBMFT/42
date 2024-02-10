NAME = push_swap.a

SRCS = main.c lists.c libft_stuff.c

OBJS = $(SRCS:.c=.o)

CC = cc

COMPRESS = ar rcs

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
			$(COMPRESS) $(NAME) $(OBJS)

clean:
			$(RM) $(OBJS)

fclean: clean
			$(RM) $(NAME)

re:		fclean all

.PHONY:			all clean fclean re