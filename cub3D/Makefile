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
CFLAGS = -Wall -Werror -Wextra

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

LIBFT_DIR = ./includes/libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = ./includes/minilibx-linux
MLX = $(MLX_DIR)/libmlx_Linux.a -lXext -lX11 -lm -lz

all: $(NAME)

bonus: $(BNAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	@cc $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MLX)
	@echo $(NAME) ready to play!

$(BNAME): $(LIBFT) $(MLX) $(BOBJS)
	@cc $(CFLAGS) -o $(BNAME) $(BOBJS) $(LIBFT) $(MLX)
	@echo $(BONUS) ready to play!

$(LIBFT):
	@echo compiling $(NAME)!
	@make -C $(LIBFT_DIR) --no-print-directory
$(MLX):
	@make -C $(MLX_DIR) #--no-print-directory

clean:
	@rm -rf $(OBJS_DIR)
	@rm -rf $(BOBJS_DIR)
	@make -C $(LIBFT_DIR) clean --no-print-directory
	@echo $(NAME) cleaned

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(BNAME)
	@make -C $(LIBFT_DIR) fclean --no-print-directory
	@make -C $(MLX_DIR) clean --no-print-directory
	@echo $(NAME) fclean

re: fclean all

.PHONY: all fclean clean re bonus
