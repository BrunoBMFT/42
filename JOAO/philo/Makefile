NAME = philo

FILES = main.c philo_init.c libft_functions.c prints.c \
		monitor.c parsing.c routine2.c routine.c
SRC_PATH = src
SRC = $(addprefix $(SRC_PATH)/, $(FILES)) 

OBJS = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra -g -pthread -fsanitize=address

all: $(NAME)

%.o: %.c
	@$(CC) -c $(CFLAGS) $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -fr $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re