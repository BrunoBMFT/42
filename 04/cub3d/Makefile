NAME = cub3D
BNAME = cub3D_bonus

SRCS_DIR = ./srcs
SRCS = main.c cub3d_init.c cub3d_init_utils.c \
		parser.c parser_map.c parser_map_utils.c parser_textures.c \
		raycast.c raycast_utils.c raycast_draw.c raycast_frame.c \
		input.c cub3d_utils.c
BSRCS_DIR = ./srcs_bonus
BSRCS = main_bonus.c cub3d_init_bonus.c cub3d_init_utils_bonus.c \
		parser_bonus.c parser_map_bonus.c parser_map_utils_bonus.c \
		parser_textures_bonus.c raycast_bonus.c raycast_utils_bonus.c \
		raycast_draw_bonus.c raycast_frame_bonus.c minimap_bonus.c \
		input_bonus.c cub3d_utils_bonus.c
		

LIBFT_URL = https://github.com/BrunoBMFT/libft_usable.git
LIBFT_DIR = ./includes/libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_URL = git@github.com:42paris/minilibx-linux.git
MLX_DIR = ./includes/minilibx-linux
MLX = $(MLX_DIR)/libmlx_Linux.a -lXext -lX11 -lm -lz
		
CFLAGS = -Wall -Werror -Wextra -g
RM = rm -rf

OBJS_DIR = ./objs
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	@cc $(CFLAGS) -c $< -o $@
BOBJS_DIR = ./objs_bonus
BOBJS = $(addprefix $(BOBJS_DIR)/, $(BSRCS:.c=.o))
$(BOBJS_DIR)/%.o: $(BSRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	@cc $(CFLAGS) -c $< -o $@

all: $(NAME)
bonus: $(BNAME)

$(NAME): $(MLX) $(LIBFT) $(OBJS)
	@cc $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MLX)
	@echo $(NAME) ready.

$(BNAME): $(LIBFT) $(MLX) $(BOBJS)
	@cc $(CFLAGS) -o $(BNAME) $(BOBJS) $(LIBFT) $(MLX)
	@echo $(BONUS) ready.

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
	@rm -rf $(BOBJS_DIR)
	@if [ -d "$(LIBFT_DIR)" ]; then \
		$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory; \
	fi

fclean: clean
	@$(RM) $(NAME)
	@rm -rf $(BNAME)
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

.PHONY: all uninstall fclean clean re bonus
