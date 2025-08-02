/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 exit.c												:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/07/26 10:52:16 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/07/26 10:55:10 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "ast.h"

static int	_non_numeric_err(char *str);
static int	_clean_and_exit(t_ctx *ctx, char **argv, int status);

int	exit_btin(int argc, char **argv, t_ctx *ctx)
{
	int		status;
	char	*str;

	if (argc == 0)
		exit(ctx->exit_status);
	if (argc != 1)
	{
		print_program_error("exit", "too many arguments");
		return (1);
	}
	str = argv[0];
	if (*str == '+' || *str == '-')
		str++;
	if (*str == '\0')
		return (_non_numeric_err(argv[0]));
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (_non_numeric_err(argv[0]));
		str++;
	}
	status = ft_atoi(argv[0]);
	return (_clean_and_exit(ctx, argv, status));
}

static int	_non_numeric_err(char *str)
{
	write(2, "exit: ", 6);
	write(2, str, ft_strlen(str));
	write(2, ": ", 2);
	write(2, "numeric argument required\n", 26);
	return (2);
}

static int	_clean_and_exit(t_ctx *ctx, char **argv, int status)
{
	free_str_array(argv);
	free_ctx(ctx);
	rl_clear_history();
	exit(status & 0xFF);
	return (0);
}
