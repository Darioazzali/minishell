/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 minishell.h										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/07/01 14:15:08 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/07/22 13:07:25 by dazzali		  ###	########.fr		  */
/*																			  */
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
# include "errors.h"
# include "log.h"
# include <sys/wait.h>

# define INITIAL_CAPACITY	10
# define HISTORY_FILE		".minishell_history"
# define MALLOC_ERROR_MSG	"Failed to allocate memory"

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
	t_list	*head;
	t_list	*last_saved;

}	t_history;

typedef struct s_ast_node	t_ast_node;

typedef struct s_ctx
{
	t_parser		*parser;
	int				pid;
	t_history		*history;
	t_envs			*envs;
	t_ast_node		*ast;
	int				exit_status;
}	t_ctx;

void			*free_ctx(t_ctx *ctx);
t_ctx			*init_ctx(void);
int				tokenize_line(t_parser *parser, const char *line);
int				expand_tokens(t_ctx *ctx);
void			*free_parser(t_ctx *ctx);
int				remove_quotes(t_ctx *ctx);
//History
t_history		*init_history(void);
void			add_to_history_struct(char *line, t_history *hist);
void			free_history_struct(t_history *hist);
void			save_to_history_file(t_history *hist);
void			load_history_from_file(t_history *hist);
int				expand_buffer(char **line, int *capacity);
int				is_empty_line(char *line);
int				recognize_tokens(t_ctx *ctx);
//Envs
void			print_vars(t_envs *envs, bool env);
t_envs			*parse_envs(char **str);
char			*get_shell_var_value(t_envs *envs, char *name);
t_sh_var		*get_shell_var(t_envs *envs, char *name);
int				set_shell_var(t_envs *envs, char *name, char *value);
void			*free_envs(t_envs *envs);
//Builtins
int				export_btin(char **av, t_envs *envs);
int				unset_btin(t_envs **envs, char **keys);
int				chdir_btin(int ac, const char **av, t_envs *envs);
int				pwd_btin(void);
int				exit_btin(int argc, char **argv, t_ctx *ctx);
//List utils
void			ft_lstadd_or_assign(t_list **head, t_list *new_node);
void			ft_lstremove_node(t_list **head,
					t_list *node, void (*del)(void *));
int				ft_strcmp(const char *s1, const char *s2);
char			**list_to_array(t_list *lst);
void			*clean_str_array(char **array, int i);
void			free_str_array(char **split_result);
bool			ft_is_whitespace(char c);
int				init_program(t_ctx **ctx, char **env);
int				read_user_line(t_ctx *ctx);
int				echo_btin(char **av);
int				ft_strcmp(const char *s1, const char *s2);
int				count_words(char **args);
char			**envs_to_strarr(t_envs *envs);
#endif
