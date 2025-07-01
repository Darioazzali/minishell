CC				=	cc
CFLAGS			=	-Wall -Wextra -g
LDFLAGS 		= -L $(MINISHELL_DIR) -lminishell -L $(LIBFT_DIR) -lft -lreadline
BUILD_DIR		=	build
SRCS_DIR		:=	srcs
SRCS_FILES		:=	test.c 
MINISHELL_DIR	=	..
INC_DIR			=	includes
CJSON_DIR 		= libs/cjson
CJSON_SRC 		= $(CJSON_DIR)/cJSON.c
CJSON_OBJ 		= $(BUILD_DIR)/cJSON.o
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
EXPORT_BTIN		= export
CD				= cd
TOKEN_RECOGNITION		= token_recognition
QUOTE_REMOVAL	= quote_removal
LIBFT_DIR		= ../libft
LIBFT			= $(LIBFT_DIR)/libft.a
UTILS			= $(BUILD_DIR)/test.o
CFLAGS 			+= -I $(CJSON_DIR)
OBJS            := $(patsubst $(SRCS_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

all: $(EXPANDER) $(TOKENIZER) $(QUOTE_REMOVAL) $(TOKEN_RECOGNITION) $(EXPORT_BTIN) $(CD)

$(EXPANDER):$(BUILD_DIR)/expander.o $(OBJS) $(CJSON_OBJ) $(LIBFT)
	make -C .. libminishell.a DEBUG=$(DEBUG)
	DEBUG=0 $(CC)  $< $(OBJS)  $(CJSON_OBJ) $(LDFLAGS)  -o $@

$(TOKENIZER):$(BUILD_DIR)/tokenizer.o $(OBJS) $(CJSON_OBJ)  $(LIBFT)
	make -C .. libminishell.a DEBUG=$(DEBUG)
	$(CC)  $< $(OBJS) $(CJSON_OBJ) $(LDFLAGS)  -o $@

$(CD):$(BUILD_DIR)/cd.o $(OBJS) $(CJSON_OBJ)  $(LIBFT)
	make -C .. libminishell.a DEBUG=$(DEBUG)
	$(CC)  $< $(OBJS) $(CJSON_OBJ) $(LDFLAGS)  -o $@

$(TOKEN_RECOGNITION):$(BUILD_DIR)/token_recognition.o $(OBJS) $(CJSON_OBJ) $(LIBFT)
	make -C .. libminishell.a DEBUG=$(DEBUG)
	$(CC)  $< $(OBJS) $(CJSON_OBJ) $(LDFLAGS)  -o $@

$(QUOTE_REMOVAL):$(BUILD_DIR)/quote_removal.o $(OBJS) $(CJSON_OBJ) $(LIBFT) force
	make -C .. libminishell.a DEBUG=$(DEBUG)
	$(CC)  $< $(OBJS) $(CJSON_OBJ) $(LDFLAGS)  -o $@

$(EXPORT_BTIN):$(BUILD_DIR)/export.o $(OBJS) $(CJSON_OBJ) $(LIBFT) force
	make -C .. libminishell.a DEBUG=$(DEBUG)
	$(CC)  $< $(OBJS) $(CJSON_OBJ) $(LDFLAGS)  -o $@

$(LIBFT): force
	echo "compiling libft"
	make -C $(LIBFT_DIR)

$(BUILD_DIR)/cJSON.o: $(CJSON_SRC)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADERS) Makefile
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) \
	-I $(LIBFT_DIR) \
	-I $(INC_DIR) \
	-I $(MINISHELL_INC) \
	-I $(MINISHELL_SRC) \
	-I libs \
	-c $< -o $@


clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(TOKENIZER) $(EXPANDER) $(TOKEN_RECOGNITION) $(QUOTE_REMOVAL)

re: fclean all

.PHONY: all clean fclean re force
