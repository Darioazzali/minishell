
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

#Source files
SRCS_FILES		=	error.c \
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
					history.c \
					history_utils.c \
					history_file.c \
					string_utils.c

HEADERS			=	$(INC_DIR)/minishell.h \
					$(SRCS_DIR)/log.h \
					$(SRCS_DIR)/parser.h

#Built-ins utilities

ECHO			=	echo
PWD				=	pwd
BUILTIN_UTILS	=	$(ECHO) $(PWD)

#Object files
SRCS			=	$(addprefix $(SRCS_DIR)/,$(SRCS_FILES))
OBJS			=	$(patsubst $(SRCS_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
DEP_FILES		=	$(OBJS:.o=.d)
UTILS_OBJS		=	$(BUILD_DIR)/error.o $(BUILD_DIR)/logger.o $(BUILD_DIR)/conversion.o

#Configuration
CONFIG_FILE		=	.build_config
DEBUG			?=	1
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
$(ECHO):$(BUILD_DIR)/echo.o $(UTILS_OBJS)
	printf "$(YELLOW)🔨 Building echo...$(RESET)\n"
	@$(CC) $< $(UTILS_OBJS) $(LIBFT) $(LDFLAGS) -o $@
	printf "$(GREEN)✅ Echo built$(RESET)\n"

$(PWD):$(BUILD_DIR)/pwd.o $(UTILS_OBJS)
	printf "$(YELLOW)🔨 Building pwd...$(RESET)\n"
	@$(CC) $< $(UTILS_OBJS) $(LIBFT) $(LDFLAGS) -o $@
	printf "$(GREEN)✅ Pwd built$(RESET)\n"

#Object files compilation
$(BUILD_DIR)/%.o:$(SRCS_DIR)/%.c $(HEADERS) Makefile $(CONFIG_FILE)
	@mkdir -p $(BUILD_DIR)
	printf "$(GREEN)Compiling: $(WHITE)$<$(RESET)\r"
	@$(CC) $(CFLAGS) \
	-D DEBUG=$(DEBUG) \
	-D LOG_FILE_PATH='"$(LOG_FILE_PATH)"' \
	-D LOG_LEVEL=$(LOG_LEVEL) \
	-I $(LIBFT_DIR) \
	-I $(INC_DIR) \
	-I $(SRCS_DIR) \
	-MD -MP \
	-c $< -o $@

# Special compilation rule for main and utilities (also generate deps)
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
		-MD -MP \
		-c $< -o $@

$(BUILD_DIR)/echo.o: $(SRCS_DIR)/echo.c Makefile $(CONFIG_FILE)
	@mkdir -p $(BUILD_DIR)
	printf "$(GREEN)Compiling: $(WHITE)$<$(RESET)\n"
	@$(CC) $(CFLAGS) \
		-D DEBUG=$(DEBUG) \
		-D LOG_FILE_PATH='"$(LOG_FILE_PATH)"' \
		-D LOG_LEVEL=$(LOG_LEVEL) \
		-I $(LIBFT_DIR) \
		-I $(INC_DIR) \
		-I $(SRCS_DIR) \
		-MD -MP \
		-c $< -o $@

$(BUILD_DIR)/pwd.o: $(SRCS_DIR)/pwd.c Makefile $(CONFIG_FILE)
	@mkdir -p $(BUILD_DIR)
	printf "$(GREEN)Compiling: $(WHITE)$<$(RESET)\n"
	@$(CC) $(CFLAGS) \
		-D DEBUG=$(DEBUG) \
		-D LOG_FILE_PATH='"$(LOG_FILE_PATH)"' \
		-D LOG_LEVEL=$(LOG_LEVEL) \
		-I $(LIBFT_DIR) \
		-I $(INC_DIR) \
		-I $(SRCS_DIR) \
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
#Include dependency files (if exists)
-include $(DEP_FILES)
