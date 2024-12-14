NAME =	cub3d

SRCS_DIR = ./srcs
SRCS = main.c parser.c parser_map.c parser_flood.c clean.c error.c prints.c
CFLAGS = -g #-Wall -Werror -Wextra

OBJS_DIR = ./objs
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	@cc $(CFLAGS) -c $< -o $@

LIBFT_DIR = ./includes/libft
LIBFT = $(LIBFT_DIR)/libft.a
$(LIBFT):
	@echo compiling $(NAME)!
	@make -C $(LIBFT_DIR) --no-print-directory

MLX_DIR = ./includes/minilibx-linux
MLX = $(MLX_DIR)/libmlx_Linux.a -lXext -lX11 -lm -lz
$(MLX):
	@make -C $(MLX_DIR) --no-print-directory

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@cc $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MLX)
	@echo $(NAME) ready to play!

clean:
	@rm -rf $(OBJS_DIR)
	@make -C $(LIBFT_DIR) clean --no-print-directory

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIBFT_DIR) fclean --no-print-directory

re: fclean all

.PHONY: all fclean clean re
