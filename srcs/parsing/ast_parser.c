/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ast_parser.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: aluque-v <aluque-v@student.42barcelon		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/06/26 16:48:47 by aluque-v		   #+#	  #+#			  */
/*	 Updated: 2025/07/23 14:32:57 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "ast.h"

static t_ast_node	*parse_logical(t_list **current);
static t_ast_node	*parse_pipeline(t_list **current);

/**
 * @brief Builds an Abstract Syntax Tree from a token stream
 * 
 * Constructs an AST using recursive descent parsing from the tokens stored in
 * the parser context. The function implements a top-down parser that respects
 * operator precedence: logical operators (&&, ||) have lowest precedence,
 * followed by pipelines (|), then commands.
 * 
 * @param ctx Pointer to the parsing context containing the token list
 *            Must not be NULL and ctx->parser->tokens
 *            should contain valid tokens
 * 
 * @return Pointer to the root node of the constructed AST on success
 * @retval NULL if no tokens are available, parsing fails,
 * 		   or memory allocation fails
 * 
 * @note The returned AST must be freed using free_ast_node()
 *       when no longer needed
 * @note Logs debug information about the parsing process and final AST structure
 * @note On failure, any constructed AST nodes are automatically cleaned up
 * 
 * @warning The function modifies the token list pointer during parsing
 * 
 * @see parse_logical(), debug_ast(), free_ast_node()
 */
t_ast_node	*build_ast(t_ctx *ctx)
{
	t_list		*current;
	t_ast_node	*ast;

	log_debug("=== Starting AST construction ===\n");
	current = ctx->parser->tokens;
	if (!current)
	{
		log_warn("No tokens to parse\n");
		return (NULL);
	}
	ast = parse_logical(&current);
	if (!ast)
	{
		log_error("Failed to build AST\n");
		return (NULL);
	}
	debug_ast(ast);
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
			return (free_ast_node(left), NULL);
		node->left = left;
		*current = (*current)->next;
		node->right = parse_logical(current);
		if (!node->right)
			return (free_ast_node(node), NULL);
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
			return (free_ast_node(left), NULL);
		node->left = left;
		*current = (*current)->next;
		node->right = parse_command(current);
		if (!node->right)
			return (free_ast_node(node), NULL);
		left = node;
	}
	return (left);
}

t_list	*flatten_pipeline_subtree(t_ast_node *node)
{
	t_list	*list;
	t_list	*right;

	if (!node || node->type != AST_PIPELINE)
		return (NULL);
	if (node->left->type == AST_PIPELINE)
	{
		list = flatten_pipeline_subtree(node->left);
		if (!list)
			return (NULL);
	}
	else
	{
		list = ft_lstnew(node->left);
		if (!list)
			return (NULL);
	}
	right = ft_lstnew(node->right);
	if (!right)
	{
		ft_lstclear(&list, NULL);
		return (NULL);
	}
	ft_lstadd_back(&list, right);
	return (list);
}

void	debug_ast(t_ast_node *ast)
{
	char	*debug_str;

	debug_str = deb_ast_to_string(ast);
	if (!debug_str)
	{
		print_error(MALLOC_ERROR_MSG);
		log_error("Failed to print AST");
		return ;
	}
	log_debug("AST construction completed:\n");
	log_debug(debug_str);
	free(debug_str);
}
