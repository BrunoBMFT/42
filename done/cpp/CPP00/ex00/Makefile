NAME = megaphone

CXX = c++
FLAGS = -Wall -Wextra -Werror -std=c++98
SRCS = megaphone.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME):$(OBJS)
	$(CXX) $(FLAGS) $(OBJS) -o $(NAME) 

%.o: %.cpp
	$(CXX) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re