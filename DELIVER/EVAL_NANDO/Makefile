NAME:=PmergeMe
CXXFLAGS:=  -g -std=c++98 -Wall -Wextra -Werror
CXX:=c++
SRCS:= main.cpp PmergeMe.cpp
OBJS:= ${patsubst %.cpp, %.o, ${SRCS}}

all: ${NAME}

${NAME}: ${OBJS}
	${CXX} ${CXXFLAGS} ${OBJS} -o ${NAME}



clean:
	rm -f ${OBJS}
fclean: clean
	rm -f ${NAME}
re: fclean all

.PHONY: all clean fclean re

