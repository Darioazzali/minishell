/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:12:17 by dazzali           #+#    #+#             */
/*   Updated: 2025/06/13 19:25:06 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdbool.h>
# include <errno.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/time.h>
# ifndef LOG_LEVEL
#  define LOG_LEVEL 2
# endif

typedef struct s_log_ctx	t_log_ctx;
typedef struct s_parser		t_parser;

typedef enum e_log_level
{
	LEVEL_DEBUG = 0,
	LEVEL_WARN = 1,
	LEVEL_ERROR = 2
}	t_log_level;

typedef struct s_ctx
{
	t_log_ctx		*logger;
	t_parser		*parser;
}	t_ctx;

/** @brief Print a program error message.
 *
 * Prints the program name followed by a colon, a space, and the error message
 * to the standard error stream.
 * If no error message is provided, the default error message "Error" is used.
 *
 * @param program_name The name of the program.
 * @param message The error message.
 */
void		print_program_error(char *program_name, char *message);

int			ltos(long usec, char *res);
void		print_error(char *message);
t_log_ctx	*init_logger(t_log_level level);
void		*free_ctx(t_ctx *ctx);
t_ctx		*init_ctx(void);
int			tokenize_line(t_ctx *ctx, char *line);
void		expand(t_ctx *ctx);
#endif
