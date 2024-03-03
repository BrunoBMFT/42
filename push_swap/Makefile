NAME = push_swap

SRCS = main.c lists.c libft_stuff.c operations.c lists2.c sort.c sort_bestfriend.c

OBJS = $(SRCS:.c=.o)

CC = cc

COMPRESS = ar rcs

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

all: $(NAME)

t: fclean $(NAME)
	./$(NAME) 10 5 9 4 7 2 3 8 5 1 6

v: fclean $(NAME)
	valgrind ./$(NAME) 10 5 9 4 7 2 3 8 5 1 6

3: fclean $(NAME)
	./$(NAME) 3 2 1
	$(RM) $(OBJS)

$(NAME): $(OBJS)
		$(CC) -o $(NAME) $(OBJS)
		@echo $(NAME) ready!

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:			all clean fclean re