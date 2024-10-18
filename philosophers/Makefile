NAME = philo
SRCS_DIR = ./srcs
OBJS_DIR = ./objs
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

SRCS = main.c logs.c parser.c init.c aux.c libft.c 

#CFLAGS = -Wall -Wextra -Werror -fsanitize=address -pthread
CFLAGS = -pthread
all: $(NAME)

$(NAME): $(OBJS)
	@cc $(CFLAGS) -o $(NAME) $(OBJS)
	@echo $(NAME) ready!

clean:
	@rm -f -r $(OBJS_DIR)
	@echo objects clean

fclean: clean
	@rm -f $(NAME)
	@echo $(NAME) fclean

re: fclean all

1:
	cc test1.c $(CFLAGS)
2:
	cc test2.c $(CFLAGS)
3:
	cc test3.c $(CFLAGS)
4:
	cc test4.c $(CFLAGS)
5:
	cc test5.c $(CFLAGS)

.PHONY: all fclean clean re