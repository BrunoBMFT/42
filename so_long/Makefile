NAME = so_long
SRCS = main.c parser.c init.c
OBJS_DIR = ./objs
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
CC = cc
COMPRESS = ar rcs
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

MLX_DIR = ./minilibx-linux
MLX = $(MLX_DIR)/libmlx_Linux.a -lXext -lX11 -lm -lz

LIBFT_DIR = ./libft

LIBFT = $(LIBFT_DIR)/libft.a

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(MLX) $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MLX)
	@echo $(NAME) ready!

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory
	@echo libft compiled and ready!

clean:
	$(RM) -r $(OBJS_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory

fclean: clean
	$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory

re: fclean all

.PHONY: all bonus fclean clean re
	
	gcc pixel_2.c -Lminilibx-linux -lmlx_Linux -lX11 -lXext

	gcc pixel_2.c -Lminilibx-linux -lmlx_Linux -lX11 -lXext && valgrind --leak-check=full --track-origins=yes ./a.out
