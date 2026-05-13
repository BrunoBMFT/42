NAME = philo

SRCS_DIR = ./srcs
SRCS = main.c libft.c parser.c init.c routine.c routine_utils.c logs.c observer.c 

OBJS_DIR = ./objs
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

CFLAGS = -Wall -Wextra -Werror -pthread -fsanitize=address

all: $(NAME)

$(NAME): $(OBJS)
	@cc $(CFLAGS) -o $(NAME) $(OBJS)
	@echo $(NAME) ready.

clean:
	@rm -f -r $(OBJS_DIR)

fclean: clean
	@rm -f $(NAME)
	@echo $(NAME) 

re: fclean all

.PHONY: all fclean clean re