NAME = philo

CC = cc -Wall -Werror -Wextra #-fsanitize=address

RM = rm -f

SRCS =	 actions.c \
		forks.c \
		init.c \
		philo.c \
		utils.c \

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME):	$(OBJ) 
			$(CC) $(OBJ) -o $(NAME)
			@echo "$(NAME) created"

clean:
			$(RM) $(OBJ)
	
fclean:		clean
				@$(RM) $(NAME)
				@echo "$(NAME) deleted"

re:			fclean all
			clear

.PHONY:		all clean fclean re
