NAME = pipex
BONUS_NAME = pipex_bonus

SRCS_DIR = ./srcs
SRCS = pipex.c pipex_aux.c
OBJS_DIR = ./objs
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

BONUS_SRCS_DIR = ./srcs_bonus
BONUS_SRCS = bonus_pipex.c bonus_pipex_aux.c
BONUS_OBJS_DIR = ./objs_bonus
BONUS_OBJS = $(addprefix $(BONUS_OBJS_DIR)/, $(BONUS_SRCS:.c=.o))
$(BONUS_OBJS_DIR)/%.o: $(BONUS_SRCS_DIR)/%.c
	@mkdir -p $(BONUS_OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

CFLAGS = -Wall -Wextra -Werror
LIBFT_DIR = ./includes/libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)
$(NAME): $(OBJS) $(LIBFT)
	@cc $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)
	@echo $(NAME) ready!

bonus: $(BONUS_NAME) 
$(BONUS_NAME): $(BONUS_OBJS) $(LIBFT) 
	@cc $(CFLAGS) -o $(BONUS_NAME) $(BONUS_OBJS) $(LIBFT)
	@echo $(BONUS_NAME) ready!

$(LIBFT):
	@echo libft compiling!
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory
	@echo libft compiled and ready!

clean:
	@rm -f -r $(OBJS_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@echo objects clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@echo pipex fclean
	
boclean:
	@rm -f -r $(BONUS_OBJS_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@echo bonus objects clean

bofclean: boclean
	@rm -f $(BONUS_NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@echo pipex bonus fclean

re: bofclean bonus

.PHONY: all bonus fclean clean re

#./pipex infile "cat" "wc" outfile
#< infile cat | wc > outfile