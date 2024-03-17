NAME = push_swap

SRCS = main.c lists.c operations.c lists2.c sort.c sort_bestfriend.c parser.c

OBJS = $(SRCS:.c=.o)

CC = cc

COMPRESS = ar rcs

CFLAGS = -Wall -Wextra -Werror -g

RM = rm -f

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

all: $(NAME)

v: 
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes

$(NAME): $(OBJS)
		$(CC) -o $(NAME) $(OBJS)
		@echo $(NAME) ready!

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:			all clean fclean re