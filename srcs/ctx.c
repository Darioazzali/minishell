/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ctx.c												:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/06/12 14:12:00 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/06/12 14:13:47 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "minishell.h"

t_ctx	*init_ctx(void)
{
	t_ctx	*ctx;

	ctx = malloc(sizeof(t_ctx));
	if (!ctx)
		return (NULL);
	ctx->pid = getpid();
	ctx->exit_status = 0;
	return (ctx);
}

void	*free_ctx(t_ctx *ctx)
{
	if (!ctx)
		return (NULL);
	if (ctx->history)
		free_history_struct(ctx->history);
	if (ctx->envs)
		free_envs(ctx->envs);
	free(ctx);
	return (NULL);
}
