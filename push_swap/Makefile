NAME = 

SRCS = push_swap.c lists.c is_sorted.c

OBJS = $(SRCS:-c=.o)

CC = CC

COMPRESS = ar rcs

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

%.o:$.CC	$(CC) -c $(CFLAGS) $?

all: $(NAME)

$(NAME): $(OBJS)
			$(COMPRESSS) $(NAME) $(OBJS)

clean:
			$(RM) $(OBJS)

fclean: clean
			$(RM) $(NAME)

re:		fclean all

.PHONY:			all clean fclean re