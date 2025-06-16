CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror -g
LDFLAGS			=	-lreadline -L $(LIBFT_DIR) -lft
NAME			=	minishell
BUILD_DIR		=	build
SRCS_DIR		:=	srcs
SRCS_FILES		:=	error.c	\
					logger.c \
					conversion.c \
					tokenizer.c \
					tokenizer2.c \
					ctx.c \
					parser_debug.c \
					parser.c	\
					expand.c	\
					expander.c	\
					expander2.c	\
					quote_removal.c \
					string_utils.c
INC_DIR			=	includes
LMINISHELL		= 	libminishell.a
HEADERS			:=	includes/minishell.h	\
					srcs/log.h	\
					srcs/parser.h
SRCS			:=	$(addprefix $(SRCS_DIR)/,$(SRCS_FILES))
ECHO			=	echo
_PWD			=	pwd
DEBUG ?= 0
LOG_FILE_PATH 	= 
LOG_LEVEL	 	= 	0
LIBFT_DIR		= libft
LIBFT			= $(LIBFT_DIR)/libft.a
UTILS			= $(BUILD_DIR)/error.o $(BUILD_DIR)/logger.o $(BUILD_DIR)/conversion.o
OBJS            := $(patsubst $(SRCS_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
CONFIG_FILE = .build_config

$(CONFIG_FILE): force
	@echo "DEBUG=$(DEBUG)" > $@.tmp
	@echo "LOG_LEVEL=$(LOG_LEVEL)" >> $@.tmp
	@if ! cmp -s $@.tmp $@ 2>/dev/null; then mv $@.tmp $@; else rm $@.tmp; fi

all: $(NAME) $(ECHO) $(_PWD)

$(NAME):$(BUILD_DIR)/main.o $(OBJS) $(LIBFT)
	$(CC)  $<  $(OBJS) $(LDFLAGS)  -o $@

$(LIBFT): force
	echo "compiling libft"
	make -C libft

$(LMINISHELL): $(OBJS)
	make $(NAME)
	ar -crs $@ $^

$(ECHO):$(BUILD_DIR)/echo.o $(UTILS)
	$(CC) $< $(UTILS) -o $@

$(_PWD):$(BUILD_DIR)/pwd.o $(UTILS)
	$(CC) $< $(UTILS) -o $@

$(BUILD_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADERS) Makefile $(CONFIG_FILE)
	@mkdir -p $(BUILD_DIR)
	echo $(LOG_FILE_PATH)
	$(CC) $(CFLAGS) -D DEBUG=$(DEBUG) \
	-D LOG_FILE_PATH='"$(LOG_FILE_PATH)"' \
	-D LOG_LEVEL=$(LOG_LEVEL) \
	-I $(LIBFT_DIR) \
	-I $(INC_DIR) -I $(SRCS_DIR) -c $< -o $@


clean:
	rm -rf $(BUILD_DIR)
	make clean -C libft

fclean: clean
	rm -f $(NAME) $(ECHO)

re: fclean all

norminette: 
	norminette $(SRCS_DIR)
	norminette $(INC_DIR)
	
.PHONY: all clean fclean re force norminette force
