NAME = libft.a

SRCS = $(addprefix srcs/, $(addsuffix .c, $(SRCDIR)))
SRCDIR =	ft_is_even ft_isalnum ft_isalpha ft_isascii ft_isdigit \
			ft_isprint ft_lstadd_back ft_lstadd_front ft_lstclear \
			ft_lstdelone ft_lstiter ft_lstlast ft_lstmap ft_lstnew \
			ft_lstsize ft_bzero ft_calloc ft_itoa \
			ft_split ft_strdup ft_strjoin ft_strmapi ft_strtrim \
			ft_substr ft_memchr ft_memcmp ft_memcpy ft_memmove \
			ft_memset ft_putchar ft_putendl ft_putnbr \
			ft_putstr ft_tolower ft_toupper ft_atoi \
			ft_strcat ft_strchr ft_striteri ft_strlcat ft_strlcpy \
			ft_strlen ft_strncmp ft_strnstr ft_strrchr ft_strcmp \
			ft_printf ft_printf_functions get_next_line get_next_line_utils

OBJDIR = ./objs
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))
$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

COMPRESS = ar rcs
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	@$(COMPRESS) $(NAME) $(OBJS)

clean:
	@$(RM) -r $(OBJDIR)

fclean: clean
	@$(RM) $(NAME)

re:  fclean $(NAME)

.PHONY: all, clean, fclean, re
