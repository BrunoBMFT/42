NAME = minishell

SRCS_DIR = ./srcs
SRCS = main.c aux.c builtins.c \
	yfrees.c yjob_list.c yjob_utils.c ylexer_utils.c ylexer.c
OBJS_DIR = ./objs
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

CFLAGS = -g
#CFLAGS = -Wall -Wextra -Werror
LIBFT_DIR = ./includes/libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@cc $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -lreadline 
	@echo $(NAME) ready!

$(LIBFT):
	@echo libft compiling!
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory
	@echo libft compiled and ready!

clean:
	@rm -f -r $(OBJS_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@echo objects clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@echo $(NAME) fclean

re: fclean all

run: all
	clear && ./minishell
vrun: all
	clear && valgrind --leak-check=full ./minishell
fullvrun: all
	clear && valgrind --leak-check=full --show-leak-kinds=all ./minishell

.PHONY: all fclean clean re
