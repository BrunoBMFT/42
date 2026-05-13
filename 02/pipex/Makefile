NAME = pipex

SRCS_DIR = ./srcs
SRCS = pipex.c pipex_aux.c errors.c

LIBFT_URL = https://github.com/BrunoBMFT/libft_usable.git
LIBFT_DIR = ./includes/libft
LIBFT = $(LIBFT_DIR)/libft.a

CFLAGS = -Wall -Wextra -Werror -g
RM = rm -rf

OBJS_DIR = ./objs
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@cc $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)
	@echo $(NAME) ready.

$(LIBFT):
	@if [ ! -d "$(LIBFT_DIR)" ]; then \
		git clone $(LIBFT_URL) $(LIBFT_DIR); \
		echo "cloned libft."; \
	fi
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

clean:
	@$(RM) $(OBJS_DIR)
	@if [ -d "$(LIBFT_DIR)" ]; then \
		$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory; \
	fi

fclean: clean
	@$(RM) $(NAME)
	@if [ -d "$(LIBFT_DIR)" ]; then \
		$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory; \
	fi
	@echo $(NAME) "fclean"

uninstall:
	@$(RM) $(LIBFT_DIR);
	@echo "libft uninstalled"

re: fclean all

.PHONY: all uninstall fclean clean re