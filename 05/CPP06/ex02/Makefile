NAME = Identify_real_type
SRCS_DIR = ./srcs
SRCS = main.cpp Base.cpp
OBJS_DIR = ./objs
OBJS = $(addprefix $(OBJS_DIR)/,$(SRCS:.cpp=.o))
CC = c++
CXXFLAGS = -g -std=c++98 -Wall -Wextra -Werror 
INCLUDES = -I includes
RM = rm -f

all: $(NAME)

$(OBJS_DIR)/%.o:  $(SRCS_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@$(CC) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	@echo "$(NAME) compiling..."
	@$(CC) $(CXXFLAGS) -o $(NAME) $(OBJS) $(INCLUDES)
	@echo "$(NAME) ready!"

clean:
	@$(RM) -r $(OBJS_DIR)
	@$(RM) -r $(OBJS_DIR_S)
	@echo "$(NAME) OBJS cleaned!"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(BONUS_NAME)
	@echo "$(NAME) cleaned!"

re: fclean all

.PHONY: all fclean clean re