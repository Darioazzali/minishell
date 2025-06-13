/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:22:26 by dazzali           #+#    #+#             */
/*   Updated: 2025/06/12 14:16:12 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOG_H
# define LOG_H
# include "minishell.h"
# ifndef DEBUG
#  define DEBUG 0
# endif
# ifndef LOG_IO
#  define LOG_IO 2
# endif
# ifndef LOG_FILE_PATH
#  define LOG_FILE_PATH 0
# endif
# define DEBUG_STR  "\x1B[34mDEBUG\x1B[0m "
# define WARN_STR   "\x1B[33mINFO\x1B[0m "
# define ERR_STR    "\x1B[31mERROR\x1B[0m "

typedef struct s_log_ctx
{
	int			fd;
	t_log_level	level;
}	t_log_ctx;

void	log_debug(t_log_ctx *ctx, char *s);
void	log_error(t_log_ctx *ctx, char *s);
void	log_warn(t_log_ctx *ctx, char *s);
#endif
