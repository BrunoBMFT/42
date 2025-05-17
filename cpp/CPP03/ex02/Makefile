NAME = ex02

SRCS_DIR = ./srcs
SRCS = main.cpp ClapTrap.cpp ScavTrap.cpp FragTrap.cpp
OBJS_DIR = ./objs
OBJS = $(addprefix $(OBJS_DIR)/,$(SRCS:.cpp=.o))
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
INCLUDES = -I includes
RM = rm -f

all: $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	@echo "$(NAME) compiling..."
	@$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS) $(INCLUDES)
	@echo "$(NAME) ready!"

clean:
	@$(RM) -r $(OBJS_DIR)
	@echo "$(NAME) OBJS cleaned!"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(NAME) cleaned!"

re: fclean all

.PHONY: all fclean clean re