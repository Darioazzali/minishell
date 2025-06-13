/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 logger.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/06/12 12:20:55 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/06/12 12:26:46 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "log.h"

static void	_log(t_log_ctx *ctx, char *s, t_log_level level);

t_log_ctx	*init_logger(t_log_level level)
{
	t_log_ctx	*ctx;
	int			fd;

	ctx = malloc(sizeof(t_log_ctx));
	if (!ctx)
	{
		print_error("Malloc error: Failed to allocate memory"
			"for logger\n");
		return (NULL);
	}
	ctx->level = level;
	if (!LOG_FILE_PATH || strlen(LOG_FILE_PATH) == 0)
		ctx->fd = STDERR_FILENO;
	else
	{
		fd = open(LOG_FILE_PATH, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
		{
			free(ctx);
			return (NULL);
		}
		else
			ctx->fd = fd;
	}
	return (ctx);
}

void	log_debug(t_log_ctx *ctx, char *s)
{
	_log(ctx, s, LEVEL_DEBUG);
}

void	log_error(t_log_ctx *ctx, char *s)
{
	_log(ctx, s, LEVEL_ERROR);
}

void	log_warn(t_log_ctx *ctx, char *s)
{
	_log(ctx, s, LEVEL_WARN);
}

static void	_log(t_log_ctx *ctx, char *s, t_log_level level)
{
	struct timeval	t;
	char			timestamp[10];
	int				log_fd;

	log_fd = ctx->fd;
	if (DEBUG == 0)
		return ;
	if (level < ctx->level)
		return ;
	gettimeofday(&t, NULL);
	ltos(t.tv_sec, timestamp);
	write(log_fd, timestamp, 10);
	write(log_fd, " ", 1);
	if (level == LEVEL_DEBUG)
		write(log_fd, DEBUG_STR, strlen(DEBUG_STR));
	else if (level == LEVEL_WARN)
		write(log_fd, WARN_STR, strlen(WARN_STR));
	else if (level == LEVEL_ERROR)
		write(log_fd, ERR_STR, strlen(ERR_STR));
	write(log_fd, s, strlen(s));
	write(log_fd, "\n", 1);
}
