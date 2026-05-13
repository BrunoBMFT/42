NAME = so_long

SRCS_DIR = ./srcs
SRCS = main.c parser.c parser_aux.c parser_flood.c init_textures.c init_textures_aux.c \
		handle_inputs.c render.c init_vars.c img.c clean.c

LIBFT_URL = https://github.com/BrunoBMFT/libft_usable.git
LIBFT_DIR = ./includes/libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_URL = git@github.com:42paris/minilibx-linux.git
MLX_DIR = ./includes/minilibx-linux
MLX = $(MLX_DIR)/libmlx_Linux.a -lXext -lX11 -lm -lz

CFLAGS = -Wall -Wextra -Werror -g
RM = rm -rf

OBJS_DIR = ./objs
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(MLX) $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MLX)
	@echo $(NAME) ready.

$(LIBFT):
	@if [ ! -d "$(LIBFT_DIR)" ]; then \
		git clone $(LIBFT_URL) $(LIBFT_DIR); \
		echo "cloned libft."; \
	fi
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory
$(MLX):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		git clone $(MLX_URL) $(MLX_DIR); \
	fi
	@$(MAKE) -C $(MLX_DIR) --no-print-directory

clean:
	@$(RM) -r $(OBJS_DIR)
	@if [ -d "$(LIBFT_DIR)" ]; then \
		$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory; \
	fi

fclean: clean
	@$(RM) $(NAME)
	@if [ -d "$(LIBFT_DIR)" ]; then \
		$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory; \
	fi
	@if [ -d "$(MLX_DIR)" ]; then \
		$(MAKE) -C $(MLX_DIR) clean --no-print-directory; \
	fi
	@echo $(NAME) "fclean"
	
uninstall:
	@$(RM) $(LIBFT_DIR);
	@$(RM) $(MLX_DIR);
	@echo "minilibx and libft uninstalled."

re: fclean all

.PHONY: all uninstall bonus fclean clean re
