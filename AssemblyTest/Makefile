NAME = test

ASRCS = functions.S
AS = nasm -felf64
CSRCS = main.c
CC = cc

OBJS_DIR = build

COBJS = $(CSRCS:%.c=$(OBJS_DIR)/%.o)
AOBJS = $(ASRCS:%.S=$(OBJS_DIR)/%.o)
OBJS = $(COBJS) $(AOBJS)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $@ $(OBJS)


$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) -c $< -o $@
$(OBJS_DIR)/%.o: %.S
	@mkdir -p $(OBJS_DIR)
	@$(AS) $< -o $@

clean:
	rm -f -r $(OBJS_DIR)
	
fclean: clean
	rm -f $(NAME)
	
re: fclean all

.PHONY: all fclean clean re