#Compiler and flags
CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror -g

# Colors and formatting
GREEN			=	\033[1;32m
BLUE			=	\033[1;34m
YELLOW			=	\033[1;33m
RED				=	\033[1;31m
PURPLE			=	\033[1;35m
CYAN			=	\033[1;36m
WHITE			=	\033[1;37m
RESET			=	\033[0m
CLEAR_LINE		=	\033[2K
MOVE_UP			=	\033[1A

#Project structure
NAME			=	minishell
BUILD_DIR		=	build
SRCS_DIR		=	srcs
INC_DIR			=	includes
LIBFT_DIR		=	libft

#Libraries
LIBFT			=	$(LIBFT_DIR)/libft.a
LMINISHELL		=	libminishell.a
LDFLAGS			=	-lreadline -L$(LIBFT_DIR) -lft

# Module directories
BUILTIN_DIR		=	$(SRCS_DIR)/builtin
CONTEXT_DIR		=	$(SRCS_DIR)/context
DEBUG_DIR		=	$(SRCS_DIR)/debug
ERRORS_DIR		=	$(SRCS_DIR)/errors
EXECUTION_DIR	=	$(SRCS_DIR)/execution
HISTORY_DIR		=	$(SRCS_DIR)/history
PARSING_DIR		=	$(SRCS_DIR)/parsing
UTILS_DIR		=	$(SRCS_DIR)/utils
VARIABLES_DIR	=	$(SRCS_DIR)/variables

# Module source files
BUILTIN_SRCS	=	cd.c echo.c export.c pwd.c unset.c exit.c
CONTEXT_SRCS	=	ctx.c
DEBUG_SRCS		=	debug_utils.c logger.c
ERRORS_SRCS		=	error.c error2.c
EXECUTION_SRCS	=	execute.c execute_command.c path.c pipeline.c redirections.c pipeline_utils.c
HISTORY_SRCS	=	history.c history_file.c history_utils.c
PARSING_SRCS	=	ast.c ast_debug2.c ast_debug.c ast_parse_command2.c \
					ast_parse_command.c ast_parser.c ast_traversal.c \
					expand.c expand2.c expander_error.c expander.c parser.c \
					parser_debug.c parse_user_line.c quote_removal.c \
					token_debug.c tokenize.c tokenizer2.c tokenizer.c \
					token_recognizing.c expand_var.c
UTILS_SRCS		=	conversion.c list_iter.c lst_utils.c string_utils.c utils.c
VARIABLES_SRCS	=	env_clean.c env_get_set.c env_parse.c variables.c

# Combine all sources with their module paths
SRCS_FILES		=	$(addprefix builtin/,$(BUILTIN_SRCS)) \
					$(addprefix context/,$(CONTEXT_SRCS)) \
					$(addprefix debug/,$(DEBUG_SRCS)) \
					$(addprefix errors/,$(ERRORS_SRCS)) \
					$(addprefix execution/,$(EXECUTION_SRCS)) \
					$(addprefix history/,$(HISTORY_SRCS)) \
					$(addprefix parsing/,$(PARSING_SRCS)) \
					$(addprefix utils/,$(UTILS_SRCS)) \
					$(addprefix variables/,$(VARIABLES_SRCS))

# Headers with module paths
HEADERS			=	$(INC_DIR)/minishell.h 		\
					$(DEBUG_DIR)/log.h 			\
					$(DEBUG_DIR)/debug.h		\
					$(PARSING_DIR)/parser.h		\
					$(PARSING_DIR)/expander.h		\
					$(PARSING_DIR)/ast.h		\
					$(PARSING_DIR)/ast_debug.h	\
					$(ERRORS_DIR)/errors.h		\
					$(VARIABLES_DIR)/env.h		\
					$(EXECUTION_DIR)/execute.h

#Built-ins utilities
# ECHO			=	echo
# EXPORT			=	export
# BUILTIN_UTILS	=	$(ECHO)

#Object files
SRCS			=	$(addprefix $(SRCS_DIR)/,$(SRCS_FILES))
OBJS			=	$(patsubst $(SRCS_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
DEP_FILES		=	$(OBJS:.o=.d)
UTILS_OBJS		=	$(BUILD_DIR)/errors/error.o \
					$(BUILD_DIR)/debug/error2.o \
					$(BUILD_DIR)/debug/logger.o \
					$(BUILD_DIR)/utils/conversion.o

#Configuration
CONFIG_FILE		=	.build_config
DEBUG			?=	0
LOG_LEVEL		=	0
LOG_FILE_PATH 	?=	

#Progress tracking
TOTAL_FILES		=	$(words $(SRCS_FILES) main echo pwd)
COMPILED_COUNT	=	0

#RULES
.SILENT:

all: header $(NAME) $(BUILTIN_UTILS) footer

header:
	printf "$(CYAN)╔══════════════════════════════════════╗$(RESET)\n"
	printf "$(CYAN)║$(WHITE)          MINISHELL BUILD            $(CYAN)║$(RESET)\n"
	printf "$(CYAN)╚══════════════════════════════════════╝$(RESET)\n"
	printf "\n"

footer:
	printf "\n$(GREEN)✅ Build completed successfully!$(RESET)\n\n"

$(NAME): $(BUILD_DIR)/main.o $(OBJS) $(LIBFT)
	printf "$(YELLOW)🔗 Linking executable...$(RESET)\n"
	@$(CC)  $< $(OBJS) $(LIBFT) $(LDFLAGS) -o $@
	printf "$(GREEN)✅ $(NAME) linked successfully$(RESET)\n"

$(LIBFT): force
	@printf "$(CLEAR_LINE)$(BLUE)📖 Building libft...$(RESET)\n"
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory
	printf "$(BLUE)✅ Libft compiled$(RESET)\n"

$(LMINISHELL): $(OBJS)
	printf "$(PURPLE)📚 Creating static library...$(RESET)\n"
	@ar -crs $@ $^
	printf "$(GREEN)✅ Library created$(RESET)\n"

#Built-in utilities
# $(ECHO):$(BUILD_DIR)/builtin/echo.o $(UTILS_OBJS)
# 	printf "$(YELLOW)🔨 Building echo...$(RESET)\n"
# 	@$(CC) $< $(UTILS_OBJS) $(LIBFT) $(LDFLAGS) -o $@
# 	printf "$(GREEN)✅ Echo built$(RESET)\n"

#Object files compilation - Updated to handle subdirectories
$(BUILD_DIR)/%.o:$(SRCS_DIR)/%.c $(HEADERS) Makefile $(CONFIG_FILE)
	@mkdir -p $(dir $@)
	printf "$(GREEN)Compiling: $(WHITE)$<$(RESET)\r"
	@$(CC) $(CFLAGS) \
	-D DEBUG=$(DEBUG) \
	-D LOG_FILE_PATH='"$(LOG_FILE_PATH)"' \
	-D LOG_LEVEL=$(LOG_LEVEL) \
	-I $(LIBFT_DIR) \
	-I $(INC_DIR) \
	-I $(SRCS_DIR) \
	-I $(DEBUG_DIR) \
	-I $(PARSING_DIR) \
	-I $(ERRORS_DIR) \
	-I $(VARIABLES_DIR) \
	-MD -MP \
	-c $< -o $@

# Special compilation rule for main
$(BUILD_DIR)/main.o: $(SRCS_DIR)/main.c Makefile $(CONFIG_FILE)
	@mkdir -p $(BUILD_DIR)
	printf "$(GREEN)Compiling: $(WHITE)$<$(RESET)\n"
	@$(CC) $(CFLAGS) \
		-D DEBUG=$(DEBUG) \
		-D LOG_FILE_PATH='"$(LOG_FILE_PATH)"' \
		-D LOG_LEVEL=$(LOG_LEVEL) \
		-I $(LIBFT_DIR) \
		-I $(INC_DIR) \
		-I $(SRCS_DIR) \
		-I $(DEBUG_DIR) \
		-I $(PARSING_DIR) \
		-I $(ERRORS_DIR) \
		-I $(VARIABLES_DIR) \
		-MD -MP \
		-c $< -o $@

#Build configuration tracking
$(CONFIG_FILE): force
	@echo "DEBUG=$(DEBUG)" > $@.tmp
	@echo "LOG_LEVEL=$(LOG_LEVEL)" >> $@.tmp
	@if ! cmp -s $@.tmp $@ 2>/dev/null; then \
		printf "$(YELLOW)⚙️  Updating build configuration...$(RESET)\n"; \
		mv $@.tmp $@ 2>/dev/null; \
		printf "$(GREEN)✅ Configuration updated$(RESET)\n"; \
	else \
		printf "$(BLUE)ℹ️  Configuration unchanged$(RESET)\n"; \
		rm $@.tmp 2>/dev/null; \
	fi

clean:
	printf "$(RED)🧹 Cleaning object files...$(RESET)\n"
	@rm -rf $(BUILD_DIR)
	@$(MAKE) clean -C $(LIBFT_DIR) --no-print-directory
	printf "$(GREEN)✅ Clean completed$(RESET)\n"

fclean: clean
	printf "$(RED)🗑️  Full clean...$(RESET)\n"
	@rm -f $(NAME) $(BUILTIN_UTILS) $(LMINISHELL) $(CONFIG_FILE)
	@$(MAKE) fclean -C $(LIBFT_DIR) --no-print-directory
	printf "$(GREEN)✅ Full clean completed$(RESET)\n"

re: fclean all

norminette: 
	printf "$(CYAN)📋 Running norminette...$(RESET)\n"
	norminette $(SRCS_DIR) $(INC_DIR)
	
.PHONY: all clean fclean re force norminette force
