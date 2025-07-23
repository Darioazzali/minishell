/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 parser.h											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/06/12 12:04:44 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/06/12 19:10:45 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "minishell.h"

typedef enum e_lexi
{
	LEXI_S_QUOTE,
	LEXI_D_QUOTE,
	LEXI_NORMAL
}	t_parser_mode;

typedef enum e_tok_type
{
	TOK_PIPE,
	TOK_AND,
	TOK_OR,
	TOK_REDIR_IN,
	TOK_REDIR_OUT,
	TOK_REDIR_APPEND,
	TOK_REDIR_HEREDOC,
	TOK_WORD,
}	t_tok_type;

typedef enum e_ast_type
{
	AST_LOGICAL,
	AST_PIPELINE,
	AST_COMMAND
}	t_ast_type;

typedef struct s_ast_node
{
	t_ast_type			type;
	char				*value;
	char				**args;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	t_list				*redirs;
	int					input_fd;
	int					output_fd;
}	t_ast_node;

typedef enum e_p_stage
{
	P_TOKENIZING,
	P_EXPANDING,
	P_QUOTES_REM,
	P_TOKEN_REC,
	P_PARSING
}	t_p_stage;

typedef struct s_parser
{
	t_parser_mode	mode;
	t_p_stage		stage;
	char			*ptr;
	char			*t_start;
	t_list			*tokens;
}	t_tokenizer;

typedef struct s_token
{
	t_tok_type	type;
	char		*value;
}	t_token;

typedef enum e_expander_error
{
	EXP_NO_ERROR,
	EXP_ERR_MALLOC,
	EXP_ERR_OTHER
}	t_expander_error;

typedef struct s_expander	t_expander;

char		*deb_format_tokens(void *lst);
char		*deb_format_tokens_type(void *lst);
char		*deb_ast_to_string(t_ast_node *node);
char		*get_token_type_str(t_tok_type tok);
int			init_expander(t_expander *expander, t_ctx *ctx, const char *token);
int			join_until_cursor(t_expander *expander);
char		*expand_shell_param(t_expander *expander);
void		*exp_error_fail(t_expander *expander);
void		*expand_err_null(t_expander *expander, t_expander_error exp_err);
int			expand_err_code(t_expander *expander, t_expander_error exp_err,
				int code);
char		*handle_metachar(t_parser *tokenizer, char *line);
bool		is_metachar(char *c);
t_ast_node	*build_ast(t_ctx *ctx);
void		free_ast_node(t_ast_node *node);
char		*deb_ast_to_string(t_ast_node *node);
void		init_tokenizer(t_parser *tokenizer, const char *line);
void		reset_tokenizer(t_parser *tokenizer, const char *line);
void		cleanup_tokenizer(t_parser *tokenizer);
void		free_token(void *token);
int			parse_line(char *line, t_ctx *ctx);
t_ast_node	*parse_new_line(char *line, t_parser *parser, t_ctx *ctx);
void		execute(t_ast_node *node, void *ctx);
// void		prepare_pipeline(t_ast_node *node, void *ctx);
void		ast_setup_pipeline(t_ast_node *ast_root, void *ctx);
int			add_token(t_tokenizer *tokenizer, char *end);
void		skip_whitespace(t_parser *tokenizer);
#endif
