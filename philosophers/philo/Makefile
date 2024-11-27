NAME = philo
SRCS_DIR = ./srcs
OBJS_DIR = ./objs
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

SRCS = main.c libft.c parser.c init.c routine.c routine_utils.c mutex.c logs.c observer.c 

CFLAGS = -Wall -Wextra -Werror -pthread -fsanitize=thread
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

.PHONY: all fclean clean re