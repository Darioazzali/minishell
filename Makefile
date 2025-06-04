CC			=	cc
NAME		=	minishell
BUILD_DIR	=	build
SRCS_DIR	:=	srcs
SRCS		:=	main.c 
SRCS		=	$(addprefix $(SRCS_DIR)/,$(SRCS))


clean:
	rm -rf $(BUILD_DIR)
fclean: clean
	rm -f $(NAME)