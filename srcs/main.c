/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 prompt.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/06/12 11:37:16 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/06/12 11:40:58 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "minishell.h"
#include "log.h"
#include <readline/readline.h>

static int	init_program(t_ctx **ctx);
static int	read_user_line(t_ctx *ctx);

int	main(void)
{
	t_ctx	*ctx;

	ctx = NULL;
	if (!init_program(&ctx))
		return (1);
	read_user_line(ctx);
	save_to_history_file(ctx->history);
	rl_clear_history();
	free_ctx(ctx);
	return (0);
}

static int	init_program(t_ctx **ctx)
{
	*ctx = init_ctx();
	if (!*ctx)
		return (0);
	(*ctx)->history = init_history();
	if (!(*ctx)->history)
	{
		perror("Error: Couldn't initialize history\n");
		return (0);
	}
	return (1);
}

static int	read_user_line(t_ctx *ctx)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (line)
		{
			add_to_history_struct(line, ctx->history);
			if (tokenize_line(ctx, line) == -1)
			{
				print_shell_error("error while parsing line");
				continue ;
			}
			if (expand_tokens(ctx) == -1)
				continue ;
			remove_quotes(ctx);
			recognize_tokens(ctx);
			free(line);
		}
		else
		{
			printf("exit\n");
			break ;
		}
	}
	return (0);
}
