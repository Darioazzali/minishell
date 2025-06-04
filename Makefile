CC			=	cc
NAME		=	minishell
BUILD_DIR	=	build

clean:
	rm -rf $(BUILD_DIR)
fclean: clean
	rm -f $(NAME)