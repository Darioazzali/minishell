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
#include "libft.h"

static void			_log(char *s, t_log_level level);
static t_log_ctx	*_get_logger_instance(void);

void	log_debug(char *s)
{
	_log(s, LEVEL_DEBUG);
}

void	log_error(char *s)
{
	_log(s, LEVEL_ERROR);
}

void	log_warn(char *s)
{
	_log(s, LEVEL_WARN);
}

static void	_log(char *s, t_log_level level)
{
	struct timeval	t;
	char			timestamp[10];
	int				log_fd;
	t_log_ctx		*ctx;

	ctx = _get_logger_instance();
	if (!ctx)
		return ;
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
		write(log_fd, DEBUG_STR, ft_strlen(DEBUG_STR));
	else if (level == LEVEL_WARN)
		write(log_fd, WARN_STR, ft_strlen(WARN_STR));
	else if (level == LEVEL_ERROR)
		write(log_fd, ERR_STR, ft_strlen(ERR_STR));
	write(log_fd, s, ft_strlen(s));
}

/** @brief Get logger instance
 *
 * Get the logger instance that is lazy initialized.
 * */
static t_log_ctx	*_get_logger_instance(void)
{
	static t_log_ctx	ctx = {0};
	static int			initialized = 0;

	if (!initialized)
	{
		ctx.level = LOG_LEVEL;
		if (!LOG_FILE_PATH || ft_strlen(LOG_FILE_PATH) == 0)
			ctx.fd = STDERR_FILENO;
		else
		{
			ctx.fd = open(LOG_FILE_PATH, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (ctx.fd < 0)
			{
				print_error("Error opening log file\n");
				ctx.fd = STDERR_FILENO;
				return (NULL);
			}
		}
		initialized = 1;
	}
	return (&ctx);
}
