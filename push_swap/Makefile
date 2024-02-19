NAME = push_swap

SRCS = main.c lists.c libft_stuff.c operations.c lists2.c sort.c

OBJS = $(SRCS:.c=.o)

CC = cc

COMPRESS = ar rcs

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) -o $(NAME) $(OBJS)
		@echo $(NAME) ready!

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:			all clean fclean re