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

int	main(int argc, char **argv, char **env)
{
	t_ctx	*ctx;

	(void) argc;
	(void) argv;
	ctx = NULL;
	if (!init_program(&ctx, env))
		return (1);
	signal(SIGINT, sig_handler_sigint);
	signal(SIGQUIT, SIG_IGN);
	read_user_line(ctx);
	save_to_history_file(ctx->history);
	rl_clear_history();
	free_ctx(ctx);
	return (ctx->exit_status);
}
