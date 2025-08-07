/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 eecute.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/07/25 14:46:31 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/07/25 14:49:00 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "execute.h"

static void	execute_command_node(t_ast_node *node, t_ctx *ctx);

void	execute(t_ast_node *node, void *content)
{
	t_ctx	*ctx;
	t_list	*flat_pipe;

	if (!content)
		return ;
	ctx = content;
	if (!node)
		return ;
	if (node->type == AST_PIPELINE)
	{
		flat_pipe = flatten_pipeline_subtree(node);
		if (!flat_pipe)
			return ;
		handle_pipeline(flat_pipe, ctx);
		ft_lstclear(&flat_pipe, NULL);
	}
	if (node->type == AST_COMMAND)
	{
		if (*node->value)
		{
			if (node->value[0] != ':')
				execute_command_node(node, ctx);
		}
		return ;
	}
}

/**	@brief Execute a single command node 
 *
 * Execute a single command node that is not part of a pipeline.
 *
 * The behaviour of the function depends on the type of the node:
 * if is a builtin, execute it in the parent process, while
 * if is a command, execute it in a child process (so fork and exec).
 *
 * @note If the command to execute is a builtin, the function
 * should handle the stdin and stdout redirections differenltly.
 * Should save the stdin and stdout, apply the redirections, and
 * then restore them.
 *
 * @note If restoration or duplication fails, the error is signaled
 * to the user using stderr. So if stderr is redirected, the error
 * may not be visible.
 * Plus if there is an error during restoration of stdin or stdout
 * the shell is lefted in a bad state. This follow the bash behaviour
*/
static void	execute_command_node(t_ast_node *node, t_ctx *ctx)
{
	if (is_builtin(node->value))
	{
		if (handle_builtin_node(node, ctx) == -1)
			return ;
	}
	else
		execute_single_command(node, ctx, node->value);
}
