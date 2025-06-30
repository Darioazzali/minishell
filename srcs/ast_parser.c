/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aluque-v <aluque-v@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:48:47 by aluque-v          #+#    #+#             */
/*   Updated: 2025/06/30 17:10:06 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "log.h"
#include "parser.h"

static t_ast_node	*parse_logical(t_list **current);
static t_ast_node	*parse_pipeline(t_list **current);
static t_ast_node	*parse_command(t_list **current);
static t_ast_node	*create_node(t_ast_type type, char *value);
static char			**list_to_array(t_list *lst);

t_ast_node	*build_ast(t_ctx *ctx)
{
	t_list		*current;
	t_ast_node	*ast;
	char		*debug_str;

	log_debug(ctx->logger, "=== Starting AST construction ===");
	current = ctx->tokenizer->tokens;
	if (!current)
	{
		log_warn(ctx->logger, "No tokens to parse");
		return (NULL);
	}
	ast = parse_logical(&current);
	if (!ast)
	{
		log_error(ctx->logger, "Failed to build AST");
		return (NULL);
	}
	//DEBUG
	debug_str = deb_ast_to_string(ast);
	log_debug(ctx->logger, "AST construction completed:");
	log_debug(ctx->logger, debug_str);
	free(debug_str);
	//DEBUG END
	return (ast);
}

static t_ast_node	*parse_logical(t_list **current)
{
	t_ast_node	*left;
	t_ast_node	*node;
	t_token		*token;

	left = parse_pipeline(current);
	if (!left)
		return (NULL);
	while (*current)
	{
		token = (t_token *)(*current)->content;
		if (token->type != TOK_AND && token->type != TOK_OR)
			break ;
		node = create_node(AST_LOGICAL, token->value);
		if (!node)
		{
			free_ast_node(node);
			return (NULL);
		}
		node->left = left;
		*current = (*current)->next;
		node->right = parse_logical(current);
		if (!node->right)
		{
			free_ast_node(node);
			return (NULL);
		}
		left = node;
	}
	return (left);
}

static t_ast_node	*parse_pipeline(t_list **current)
{
	t_ast_node	*left;
	t_ast_node	*node;
	t_token		*token;

	left = parse_command(current);
	if (!left)
		return (NULL);
	while (*current)
	{
		token = (t_token *)(*current)->content;
		if (token->type != TOK_PIPE)
			break ;
		node = create_node(AST_PIPELINE, token->value);
		if (!node)
		{
			free_ast_node(left);
			return (NULL);
		}
		node->left = left;
		*current = (*current)->next;
		node->right = parse_command(current);
		if (!node->right)
		{
			free_ast_node(node);
			return (NULL);
		}
		left = node;
	}
	return (left);
}

static t_ast_node	*parse_command(t_list **current)
{
	t_ast_node	*cmd;
	t_token		*token;
	t_list		*args;

	if (!*current)
		return (NULL);
	token = (t_token *)(*current)->content;
	if (token->type != TOK_WORD)
		return (NULL);
	cmd = create_node(AST_COMMAND, token->value);
	if (!cmd)
		return (NULL);
	*current = (*current)->next;
	args = NULL;
	while (*current)
	{
		token = (t_token *)(*current)->content;
		if (token->type != TOK_WORD)
			break ;
		ft_lstadd_back(&args, ft_lstnew(ft_strdup(token->value)));
		*current = (*current)->next;
	}
	if (args)
	{
		cmd->args = list_to_array(args);
		ft_lstclear(&args, free);
	}
	return (cmd);
}

static t_ast_node	*create_node(t_ast_type type, char *value)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->value = ft_strdup(value);
	node->args = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

static char	**list_to_array(t_list *lst)
{
	int		size;
	char	**array;
	int		i;

	if (!lst)
		return (NULL);
	size = ft_lstsize(lst);
	i = 0;
	array = malloc(sizeof(char *) * (size + 1));
	if (!array)
		return (NULL);
	while (lst)
	{
		array[i] = ft_strdup((char *)lst->content);
		if (!array[i])
		{
			while (--i >= 0)
				free(array[i]);
			free(array);
			return (NULL);
		}
		lst = lst->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}
