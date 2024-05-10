NAME = pipex
SRCS_DIR = ./srcs
SRCS = pipex.c pipex_aux.c
OBJS_DIR = ./objs
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
CC = cc
COMPRESS = ar rcs
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

LIBFT_DIR = ./includes/libft
LIBFT = $(LIBFT_DIR)/libft.a

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
		@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)
		@echo $(NAME) ready!

$(LIBFT):
		@$(MAKE) -C $(LIBFT_DIR) --no-print-directory
		@echo libft compiled and ready!

clean:
		@$(RM) -r $(OBJS_DIR)
		@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
		@echo objects clean

fclean: clean
		@$(RM) $(NAME)
		@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
		@echo pipex fclean

re: fclean all

.PHONY: all bonus fclean clean re

#./pipex infile "cat" "wc" outfile
#< infile cat | wc > outfile