/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:15:08 by dazzali           #+#    #+#             */
/*   Updated: 2025/07/17 08:37:28 by dazzali          ###   ########.fr       */
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

# define INITIAL_CAPACITY	10
# define HISTORY_FILE		".minishell_history"
# define MALLOC_ERROR_MSG	"Failed to allocate memory"

typedef struct s_log_ctx	t_log_ctx;
typedef struct s_parser		t_parser;
typedef struct s_sh_var
{
	char	*name;
	char	*value;
	bool	exported;
}	t_sh_var;
typedef t_list				t_envs;

typedef struct s_history
{
	char	**commands;
	int		count;
	int		capacity;
}	t_history;

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
	t_envs			*envs;
	int				exit_status;
}	t_ctx;

int				ltos(long usec, char *res);
void			print_program_error(char *program_name, char *message);
void			print_error(char *message);
void			print_shell_error(char *message);
void			*print_shell_error_ret_null(char *message);
t_log_ctx		*init_logger(t_log_level level);
void			*free_ctx(t_ctx *ctx);
t_ctx			*init_ctx(void);
int				tokenize_line(t_ctx *ctx, const char *line);
int				expand_tokens(t_ctx *ctx);
void			*free_parser(t_ctx *ctx);
int				remove_quotes(t_ctx *ctx);
bool			ft_is_whitespace(char c);
//History
t_history		*init_history(void);
void			add_to_history_struct(char *line, t_history *hist);
void			free_history_struct(t_history *hist);
void			save_to_history_file(t_history *hist);
void			load_history_from_file(t_history *hist);
int				expand_buffer(char **line, int *capacity);
int				is_empty_line(char *line);
int				recognize_tokens(t_ctx *ctx);
void			print_vars(t_envs *envs, bool env);
t_envs			*parse_envs(char **str);
char			*get_shell_var_value(t_envs *envs, char *name);
t_sh_var		*get_shell_var(t_envs *envs, char *name);
int				set_shell_var(t_envs *envs, char *name, char *value);
void			_export_var(t_envs *envs, char *name, char *value);
int				export_builtin(char **av, t_envs *envs);
t_sh_var		*parse_variable_assignment(char *str);
void			ft_lstremove_node(t_list **head,
					t_list *node, void (*del)(void *));
int				unset_builtin(t_envs **envs, char **keys);
void			*free_envs(t_envs *envs);
void			free_split_result(char **split_result);
#endif
