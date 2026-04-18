NAME = libft_malloc.a
TESTNAME = testing

SRCS = malloc.c

OBJS = $(SRCS:.c=.o)

COMPRESS = ar rcs

RM = rm -f

%.o: %.c
	$(CC) -c $(CFLAGS) $?

all: $(NAME)
	$(CC) testing.c $(NAME) -o $(TESTNAME)

$(NAME): $(OBJS)
	$(COMPRESS) $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS) $(BONUS_OBJS)

fclean: clean
	$(RM) $(NAME)

re:  fclean all

.PHONY: all, clean, fclean, re
