
NAME = so_long

SRCS = map.c

OBJS_DIR = ./objs

OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

CC = cc

COMPRESS = ar rcs

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

LIBFT_DIR = ./libft

LIBFT = $(LIBFT_DIR)/libft.a

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(MLX) $(OBJS) $(LIBFT)
	@$(CC) -o $(NAME) $(OBJS) $(LIBFT)
	@echo $(NAME) ready!

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

MLX_DIR = ./includes/minilibx-linux
MLX = $(MLX_DIR)/libmlx_Linux.a -lmlx_Linux-lXext -lX11 -lm

clean:
		$(RM) -r $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all bonus fclean clean re
	
	gcc img_test.c -Lminilibx-linux -lmlx_Linux -lX11 -lXext