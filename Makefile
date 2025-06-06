CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
NAME		=	minishell
BUILD_DIR	=	build
SRCS_DIR	:=	srcs
SRCS		:=	main.c	\
				echo.c
INC_DIR		=	includes
HEADERS		:=	minishell.h
HEADERS		:=	$(addprefix $(INC_DIR)/,$(HEADERS))
SRCS		=	$(addprefix $(SRCS_DIR)/,$(SRCS))
ECHO		=	echo

all:$(ECHO)

$(BUILD_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADERS) Makefile
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(ECHO):$(BUILD_DIR)/echo.o
	$(CC) $< -o $@

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME) $(ECHO)

re: fclean all
