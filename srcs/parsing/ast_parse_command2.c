/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ast_parse_command2.c								:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/07/23 18:37:07 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/07/24 14:35:40 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "ast.h"

t_token_category	classify_token(t_token *token)
{
	if (!token)
		return (TOKEN_UNKNOWN);
	if (token->type == TOK_PIPE
		|| token->type == TOK_AND || token->type == TOK_OR)
		return (TOKEN_COMMAND_END);
	if (token->type == TOK_REDIR_IN || token->type == TOK_REDIR_OUT
		|| token->type == TOK_REDIR_APPEND || token->type == TOK_REDIR_HEREDOC)
		return (TOKEN_REDIRECTION);
	if (token->type == TOK_WORD)
		return (TOKEN_WORD);
	return (TOKEN_UNKNOWN);
}

void	free_command_parts(t_command_parts *parts)
{
	if (!parts)
		return ;
	free(parts->com_name);
	ft_lstclear(&parts->args_list, free);
	ft_lstclear(&parts->redirections, free_redir_struct);
	free(parts);
}

t_command_parts	*init_command_parts(void)
{
	t_command_parts	*parts;

	parts = malloc(sizeof(t_command_parts));
	if (!parts)
		return (NULL);
	parts->com_name = NULL;
	parts->args_list = NULL;
	parts->redirections = NULL;
	return (parts);
}

t_ast_node	*build_ast_node(t_command_parts *parts)
{
	t_ast_node	*node;

	if (!parts->com_name)
	{
		parts->com_name = ft_strdup(":");
		if (!parts->com_name)
			return (NULL);
	}
	node = create_node(AST_COMMAND, parts->com_name);
	if (!node)
		return (NULL);
	if (parts->args_list)
	{
		node->args = list_to_array(parts->args_list);
		if (!node->args)
		{
			free_ast_node(node);
			return (NULL);
		}
	}
	else
		node->args = NULL;
	node->redirs = parts->redirections;
	parts->redirections = NULL;
	return (node);
}

/** @brief Creates a redirection node
 *	Creates a new node for the ast node
 * @param redir_token The type of the node
 * @param file_token The value of the node
 *
 * @note The value is duplicated
 * */
t_list	*init_redir_node(t_token *redir_token, t_token *file_token)
{
	t_redir	*redir;
	t_list	*redir_node;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (print_shell_error_ret_null(MALLOC_ERROR_MSG));
	redir->type = redir_token->type;
	redir->target = ft_strdup(file_token->value);
	if (!redir->target)
	{
		free(redir);
		return (print_shell_error_ret_null(MALLOC_ERROR_MSG));
	}
	redir_node = ft_lstnew(redir);
	if (!redir_node)
	{
		free(redir->target);
		free(redir);
		return (print_shell_error_ret_null(MALLOC_ERROR_MSG));
	}
	return (redir_node);
}
