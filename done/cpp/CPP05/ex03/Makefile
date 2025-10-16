NAME = ex03
SRCS_DIR = ./srcs
SRCS =	main.cpp Bureaucrat.cpp AForm.cpp \
		ShrubberyCreationForm.cpp RobotomyRequestForm.cpp \
		PresidentialPardonForm.cpp Intern.cpp
OBJS_DIR = ./objs
OBJS = $(addprefix $(OBJS_DIR)/,$(SRCS:.cpp=.o))
CXX = c++
CXXFLAGS = -g -std=c++98 -Wall -Wextra -Werror 
INCLUDES = -I includes
RM = rm -f

all: $(NAME)

$(OBJS_DIR)/%.o:  $(SRCS_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	@echo "$(NAME) compiling..."
	@$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS) $(INCLUDES)
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