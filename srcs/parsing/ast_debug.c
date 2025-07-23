/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ast_debug.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/06/30 17:12:44 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/06/30 17:13:07 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "ast_debug.h"

static void	ast_to_string_recursive(t_ast_node *node, char **result, int depth);
static void	append_indent(char **result, int depth);

char	*deb_ast_to_string(t_ast_node *node)
{
	char	*result;

	if (!node)
		return (ft_strdup("(null)"));
	result = ft_strdup("\n");
	ast_to_string_recursive(node, &result, 0);
	return (result);
}

static void	ast_to_string_recursive(t_ast_node *node, char **result, int depth)
{
	char	*temp;
	char	*line;

	if (!node)
		return ;
	line = malloc(BUF_SIZE);
	append_indent(&line, depth);
	append_node_type(line, node);
	if (node->type == AST_COMMAND && node->args)
		debug_ast_command_args(line, node);
	if (node->type == AST_COMMAND && node->redirs)
		debug_ast_command_redirs(line, node, depth);
	if (node->type == AST_COMMAND)
		debug_ast_commands_fds(line, node, depth);
	ft_strlcat(line, "\n", BUF_SIZE);
	temp = ft_strjoin(*result, line);
	free(*result);
	free(line);
	*result = temp;
	if (node->left)
		ast_to_string_recursive(node->left, result, depth + 1);
	if (node->right)
		ast_to_string_recursive(node->right, result, depth + 1);
}

static void	append_indent(char **line, int depth)
{
	int	i;

	ft_strlcpy(*line, "", BUF_SIZE);
	i = 0;
	while (i < depth)
	{
		ft_strlcat(*line, "    ", BUF_SIZE);
		i++;
	}
}
