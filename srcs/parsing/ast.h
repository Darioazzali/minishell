/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ast.h												:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/07/23 15:01:10 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/07/23 17:39:30 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H
# define BUF_SIZE 1024
# include "parser.h"

typedef struct s_redir
{
	t_tok_type	type;
	char		*target;
}	t_redir;

typedef enum e_token_category
{
	TOKEN_COMMAND_END,
	TOKEN_REDIRECTION,
	TOKEN_WORD,
	TOKEN_UNKNOWN
}	t_token_category;

typedef struct s_command_parts
{
	char	*com_name;
	t_list	*args_list;
	t_list	*redirections;
}	t_command_parts;

typedef struct list_iter
{
	t_list	*lst;
}	t_lst_iter;

t_ast_node			*create_node(t_ast_type type, char *value);
void				free_redir_struct(void	*content);
t_ast_node			*parse_command(t_list **current);
t_token_category	classify_token(t_token *token);
void				free_command_parts(t_command_parts *parts);
t_command_parts		*init_command_parts(void);
t_ast_node			*build_ast_node(t_command_parts *parts);
t_list				*init_redir_node(t_token *redir_token, t_token *file_token);
void				debug_ast(t_ast_node *ast);
void				build_lst_iter(t_lst_iter *iter, t_list *lst);
bool				lst_iter_is_valid(t_lst_iter *iter);
t_token				*lst_iter_current(t_lst_iter *iter);
void				lst_iter_advance(t_lst_iter *iter);
int					traverse_ast(t_ast_node	*node,
						void (*visit)(t_ast_node *, void*),
						void *ctx);
#endif
