NAME = libft.a

SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlcat.c \
ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c \
ft_substr.c ft_tolower.c ft_toupper.c ft_strmapi.c ft_striteri.c ft_printf.c \
ft_printf_functions.c ft_printf_putnbr.c get_next_line.c get_next_line_utils.c \
ft_atol.c 

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
