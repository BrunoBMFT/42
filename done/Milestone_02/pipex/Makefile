NAME = pipex
BONUS_NAME = pipex_bonus

SRCS_DIR = ./srcs
SRCS = pipex.c pipex_aux.c errors.c
OBJS_DIR = ./objs
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

BONUS_SRCS_DIR = ./srcs_bonus
BONUS_SRCS = bonus_pipex.c bonus_pipex_aux.c
BONUS_OBJS_DIR = ./objs_bonus
BONUS_OBJS = $(addprefix $(BONUS_OBJS_DIR)/, $(BONUS_SRCS:.c=.o))
$(BONUS_OBJS_DIR)/%.o: $(BONUS_SRCS_DIR)/%.c
	@mkdir -p $(BONUS_OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

CFLAGS = -Wall -Wextra -Werror
LIBFT_DIR = ./includes/libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@cc $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)
	@echo $(NAME) ready!

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJS) $(LIBFT) 
	@cc $(CFLAGS) -o $(BONUS_NAME) $(BONUS_OBJS) $(LIBFT)
	@echo $(BONUS_NAME) ready!

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

clean:
	@rm -f -r $(OBJS_DIR) $(BONUS_OBJS_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory

fclean: clean
	@rm -f $(NAME) $(BONUS_NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@echo fclean

re: fclean all

.PHONY: all bonus fclean clean re