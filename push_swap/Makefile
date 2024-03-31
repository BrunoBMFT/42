NAME = push_swap

SRCS = main.c lists.c operations.c lists2.c sort.c sort_bestfriend.c parser.c \
sort_cost.c sort_aux.c ft_printf.c median.c

OBJDIR = ./objs

OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

CC = cc

COMPRESS = ar rcs

CFLAGS = -Wall -Wextra -Werror -g

RM = rm -f

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

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