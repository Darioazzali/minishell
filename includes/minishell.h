/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:12:17 by dazzali           #+#    #+#             */

/*   Updated: 2025/06/15 18:09:15 by aluque-v         ###   ########.fr       */
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
# include <string.h>
# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/time.h>
# ifndef LOG_LEVEL
#  define LOG_LEVEL 2
# endif

# define MALLOC_ERROR_MSG	"Failed to allocate memory"
# define HISTORY_FILE		".minishell_history"
# define INITIAL_CAPACITY	10;
typedef struct s_log_ctx	t_log_ctx;
typedef struct s_parser		t_parser;
typedef struct s_history	t_history;

typedef enum e_log_level
{
	LEVEL_DEBUG = 0,
	LEVEL_WARN = 1,
	LEVEL_ERROR = 2
}	t_log_level;

typedef struct s_ctx
{
	t_log_ctx		*logger;
	t_parser		*tokenizer;
	int				pid;
	t_history		*history;
	int				exit_status;
}	t_ctx;

typedef struct s_history
{
	char	**commands;
	int		count;
	int		capacity;
}	t_history;

int			ltos(long usec, char *res);
void		print_program_error(char *program_name, char *message);
void		print_error(char *message);
void		print_shell_error(char *message);
t_log_ctx	*init_logger(t_log_level level);
void		*free_ctx(t_ctx *ctx);
t_ctx		*init_ctx(void);
int			tokenize_line(t_ctx *ctx, const char *line);
int			expand_tokens(t_ctx *ctx);
void		*free_parser(t_ctx *ctx);
int			remove_quotes(t_ctx *ctx);
bool		ft_is_whitespace(char c);

//History
t_history	*init_history(void);
void		add_to_history_struct(char *line, t_history *hist);
void		save_to_history_file(t_history *hist);
#endif
