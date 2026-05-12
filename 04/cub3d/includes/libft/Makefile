NAME = libft.a

SRCS = $(addprefix srcs/,$(addsuffix .c, $(SRCFLD)))
SRCFLD = $(addprefix is/, $(IS_SRCS)) $(addprefix list/, $(LIST_SRCS)) $(addprefix mall/, $(MALL_SRCS)) \
$(addprefix mem/, $(MEM_SRCS)) $(addprefix put/, $(PUT_SRCS)) $(addprefix str/, $(STR_SRCS)) \
$(addprefix printf/, $(PRINTF_SRCS)) $(addprefix gnl/, $(GNL_SRCS))

IS_SRCS = ft_is_even ft_isalnum ft_isalpha ft_isascii ft_isdigit ft_isprint
LIST_SRCS = ft_lstadd_back ft_lstadd_front ft_lstclear ft_lstdelone ft_lstiter ft_lstlast \
ft_lstmap ft_lstnew ft_lstsize
MALL_SRCS = ft_bzero ft_calloc ft_free_array ft_itoa ft_split ft_strdup ft_strjoin \
ft_strmapi ft_strtrim ft_substr
MEM_SRCS = ft_memchr ft_memcmp ft_memcpy ft_memmove ft_memset
PUT_SRCS = ft_putchar_fd ft_putendl_fd ft_putnbr_fd ft_putstr_fd ft_tolower ft_toupper
STR_SRCS = ft_atoi ft_atol ft_strcat ft_strchr ft_striteri ft_strlcat ft_strlcpy \
ft_strlen ft_strncmp ft_strnstr ft_strrchr ft_strcmp
PRINTF_SRCS = ft_printf ft_printf_functions
GNL_SRCS = get_next_line get_next_line_utils

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
