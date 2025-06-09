CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g
NAME		=	minishell
BUILD_DIR	=	build
SRCS_DIR	:=	srcs
SRCS		:=	main.c	\
				echo.c	\
				error.c	
INC_DIR		=	includes
HEADERS		:=	$(INC_DIR)/minishell.h 
SRCS		=	$(addprefix $(SRCS_DIR)/,$(SRCS))
ECHO		=	echo
_PWD		=	pwd
UTILS		= $(BUILD_DIR)/error.o

all:$(ECHO) $(PWD)

$(BUILD_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADERS) Makefile
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -I $(SRCS_DIR) -c $< -o $@

$(ECHO):$(BUILD_DIR)/echo.o $(UTILS)
	$(CC) $< $(UTILS) -o $@

$(_PWD):$(BUILD_DIR)/pwd.o $(UTILS)
	$(CC) $< $(UTILS) -o $@

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME) $(ECHO)

re: fclean all
