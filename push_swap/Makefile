NAME = push_swap
SRCS_DIR = ./srcs
SRCS = main.c lists.c operations.c lists2.c sort.c sort_bestfriend.c parser.c \
sort_cost.c sort_aux.c median.c
OBJDIR = ./objs
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))
LIBFT_DIR = ./includes/libft
LIBFT = $(LIBFT_DIR)/libft.a
CC = cc
COMPRESS = ar rcs
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f
$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)
	@echo $(NAME) ready!

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory
	@echo libft compiled and ready!

clean:
	@$(RM) -r $(OBJDIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@echo objects clean

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@echo push_swap fclean

re:		fclean all

.PHONY:			all clean fclean re