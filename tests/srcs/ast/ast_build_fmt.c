/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_build_fmt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 13:58:13 by dazzali           #+#    #+#             */
/*   Updated: 2025/07/25 14:01:34 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_test.h"

static void	_append_redir(t_list *node);
static void	_append_args(char **args);
static void	append_node_to_string(t_ast_node *node);

void	test_visit(t_ast_node *node, void *ctx)
{
	ctx = NULL;
	if (!node)
		return ;
	append_node_to_string(node);
	test_visit(node->left, ctx);
	test_visit(node->right, ctx);
	if (node->type == AST_PIPELINE || node->type == AST_LOGICAL)
		strcat(g_buff, ")");
}

static void	append_node_to_string(t_ast_node *node)
{
	if (!node)
		return ;
	if (strlen(g_buff) > 0)
		strcat(g_buff, ",");
	if (node->type == AST_COMMAND)
	{
		strcat(g_buff, "cmd:");
		if (node->value)
			strcat(g_buff, node->value);
		if (node->args)
			_append_args(node->args);
		if (node->redirs)
		{
			_append_redir(node->redirs);
		}
	}
	else if (node->type == AST_PIPELINE)
		strcat(g_buff, "pipe(");
	else if (node->type == AST_LOGICAL)
		strcat(g_buff, "logical(");
}

static void	_append_args(char **args)
{
	size_t	i;

	strcat(g_buff, "[");
	i = 0;
	while (args[i])
	{
		if (i > 0)
			strcat(g_buff, ",");
		strcat(g_buff, args[i]);
		i++;
	}
	strcat(g_buff, "]");
}

static void	_append_redir(t_list *node)
{
	t_redir	*redir;
	bool	first;

	strcat(g_buff, "{");
	first = true;
	while (node)
	{
		if (first)
			first = false;
		else
			strcat(g_buff, ",");
		redir = node->content;
		if (redir->type == TOK_REDIR_IN)
			strcat(g_buff, "<");
		else if (redir->type == TOK_REDIR_OUT)
			strcat(g_buff, ">");
		else if (redir->type == TOK_REDIR_APPEND)
			strcat(g_buff, ">>");
		strcat(g_buff, redir->target);
		node = node->next;
	}
	strcat(g_buff, "}");
}

