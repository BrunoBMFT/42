NAME = libftprintf.a

CC = cc -Wall -Wextra -Werror
COMPRESS = ar rcs
RM = rm -rf

SRC_DIR = ./srcs
SRCS = ft_printf.c ft_printf_functions.c ft_putnbr.c

OBJ_DIR = ./objs
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@$(COMPRESS) $(NAME) $(OBJS)
	cc main.c libftprintf.a
	@echo compiled

clean:
	@$(RM) $(OBJ_DIR)

fclean:	clean
	@$(RM) $(NAME)
	@echo fclean

re: fclean all

.PHONY: all clean fclean re

