/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:22:26 by dazzali           #+#    #+#             */
/*   Updated: 2025/07/28 07:37:20 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOG_H
# define LOG_H
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
# include "libft.h"
# include <sys/time.h>
# include "errors.h"
# include <unistd.h>
# include <fcntl.h>

typedef enum e_log_level
{
	LEVEL_DEBUG = 0,
	LEVEL_WARN = 1,
	LEVEL_ERROR = 2
}	t_log_level;

typedef struct s_log_ctx
{
	int			fd;
	t_log_level	level;
}	t_log_ctx;

void	log_debug(char *s);
void	log_error(char *s);
void	log_warn(char *s);
int		ltos(long nbr, char *res);
void	log_debug_struct(void *str, char *(*fmt) (void *));
#endif
