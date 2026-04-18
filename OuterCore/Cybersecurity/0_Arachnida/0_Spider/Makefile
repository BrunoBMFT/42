NAME = spider

SRC = spider.cpp
OBJ = $(SRC:.cpp=.o)
CXX = c++
CXXFLAGS = -g
RM = rm -rf

all: $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(NAME): $(OBJ) 
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ)

clean: 
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
	