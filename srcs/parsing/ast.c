/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ast.c												:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/07/23 15:02:28 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/07/23 15:43:21 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "ast.h"

/** @brief Creates a node
 *	Creates a new node for the Recursive Descent Parser
 *	@param type The type of the node
 *	@param value The value of the node
 *
 *	@note The value is duplicated
 *	@warning This function duplicated value
 *			 so can fail if the allocation fails
 *
 *	@return A pointer to the new node or NULL
 *
 * @
 * */
t_ast_node	*create_node(t_ast_type type, char *value)
{
	t_ast_node	*node;

	if (!value)
	{
		return (print_shell_error_ret_null("No command value"));
	}
	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->value = ft_strdup(value);
	if (!node->value)
	{
		print_error(MALLOC_ERROR_MSG);
		free(node);
		return (NULL);
	}
	node->input_fd = STDIN_FILENO;
	node->output_fd = STDOUT_FILENO;
	node->args = NULL;
	node->left = NULL;
	node->right = NULL;
	node->redirs = NULL;
	return (node);
}

void	free_ast_node(t_ast_node *node)
{
	int	i;

	if (!node)
		return ;
	free(node->value);
	if (node->args)
	{
		i = 0;
		while (node->args[i])
		{
			free(node->args[i]);
			i++;
		}
		free(node->args);
	}
	free_ast_node(node->left);
	free_ast_node(node->right);
	if (node->redirs)
		ft_lstclear(&node->redirs, free_redir_struct);
	free(node);
}

void	free_redir_struct(void *content)
{
	t_redir	*redir;

	redir = content;
	if (!redir)
		return ;
	if (redir->target)
		free(redir->target);
	free(redir);
}
