NAME:=RPN
CXXFLAGS:= -g -std=c++98 -Wall -Werror -Wextra
CXX:= c++

SRCS:=main.cpp RPN.cpp 
OBJS:= ${patsubst %.cpp, %.o, ${SRCS}}


all: ${NAME}

${NAME}: ${OBJS}
	${CXX} ${CXXFLAGS} ${OBJS} -o ${NAME}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: re fclean clean all

