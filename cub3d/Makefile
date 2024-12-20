NAME =	cub3d

SRCS_DIR = ./srcs
SRCS = main.c parser.c parser_map.c parser_flood.c init_textures.c clean.c error.c input.c 
CFLAGS = -g #-Wall -Werror -Wextra

OBJS_DIR = ./objs
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	@cc $(CFLAGS) -c $< -o $@

LIBFT_DIR = ./includes/libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = ./includes/minilibx-linux
MLX = $(MLX_DIR)/libmlx_Linux.a -lXext -lX11 -lm -lz

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	@cc $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MLX)
	@echo $(NAME) ready to play!

$(LIBFT):
	@echo compiling $(NAME)!
	@make -C $(LIBFT_DIR) --no-print-directory
$(MLX):
	@make -C $(MLX_DIR) #--no-print-directory
	@echo $(MLX) compiled and ready!

clean:
	@rm -rf $(OBJS_DIR)
	@make -C $(LIBFT_DIR) clean --no-print-directory
fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIBFT_DIR) fclean --no-print-directory

#remove
clean_mlx:
	@rm -rf $(OBJS_DIR)
	@make -C $(LIBFT_DIR) clean --no-print-directory
	@make -C $(MLX_DIR) clean --no-print-directory
fullclean: clean_mlx
	@rm -rf $(NAME)
	@make -C $(LIBFT_DIR) fclean --no-print-directory

re: fclean all

.PHONY: all fclean clean re
