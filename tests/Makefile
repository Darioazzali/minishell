CC				=	cc
CFLAGS			=	-Wall -Wextra -g
LDFLAGS			=	-L $(MINISHELL_DIR) -lminishell -L $(LIBFT_DIR) -lft 
BUILD_DIR		=	build
SRCS_DIR		:=	srcs
SRCS_FILES		:=	test.c 
MINISHELL_DIR	=	..
INC_DIR			=	includes
MINISHELL_INC	=	$(MINISHELL_DIR)/includes
MINISHELL_SRC	=	$(MINISHELL_DIR)/srcs
MINISHELL_OBJ	=	$(wildcard $(MINISHELL_DIR)/build/*.o)
HEADERS			:=	includes/test.h
SRCS			:=	$(addprefix $(SRCS_DIR)/,$(SRCS_FILES))
DEBUG			?=	0
# LOG_FILE_PATH 	= 
# LOG_LEVEL	 	= 	0
EXPANDER		= expander
TOKENIZER		= tokenizer
QUOTE_REMOVAL	= quote_removal
LIBFT_DIR		= ../libft
LIBFT			= $(LIBFT_DIR)/libft.a
UTILS			= $(BUILD_DIR)/test.o
OBJS            := $(patsubst $(SRCS_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

all: $(EXPANDER) $(TOKENIZER) $(QUOTE_REMOVAL)

$(EXPANDER):$(BUILD_DIR)/expander.o $(OBJS) $(LIBFT)
	make -C .. DEBUG=$(DEBUG)
	DEBUG=0 $(CC)  $< $(OBJS)  $(LDFLAGS)  -o $@

$(TOKENIZER):$(BUILD_DIR)/tokenizer.o $(OBJS) $(LIBFT)
	make -C .. libminishell.a DEBUG=$(DEBUG)
	$(CC)  $< $(OBJS)  $(LDFLAGS)  -o $@

$(QUOTE_REMOVAL):$(BUILD_DIR)/quote_removal.o $(OBJS) $(LIBFT) force
	make -C .. libminishell.a DEBUG=$(DEBUG)
	$(CC)  $< $(OBJS)  $(LDFLAGS)  -o $@

$(LIBFT): force
	echo "compiling libft"
	make -C $(LIBFT_DIR)

$(BUILD_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADERS) Makefile
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) \
	-I $(LIBFT_DIR) \
	-I $(INC_DIR) \
	-I $(MINISHELL_INC) \
	-I $(MINISHELL_SRC) \
	-c $< -o $@


clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(TOKENIZER) $(EXPANDER)

re: fclean all

.PHONY: all clean fclean re force
