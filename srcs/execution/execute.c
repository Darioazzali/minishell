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
		execute_command_node(node, ctx);
		return ;
	}
}

static void	execute_command_node(t_ast_node *node, t_ctx *ctx)
{
	char	*prog_name;

	prog_name = node->value;
	if (is_builtin(prog_name))
		execute_btin(prog_name, node->args, ctx);
	else
		execute_single_command(node, ctx, prog_name);
}

bool	is_builtin(char *command)
{
	if (ft_strcmp(command, "pwd") == 0)
		return (true);
	if (ft_strcmp(command, "cd") == 0)
		return (true);
	if (ft_strcmp(command, "export") == 0)
		return (true);
	if (ft_strcmp(command, "unset") == 0)
		return (true);
	if (ft_strcmp(command, "exit") == 0)
		return (true);
	if (ft_strcmp(command, "echo") == 0)
		return (true);
	return (false);
}

int	execute_btin(char *prog_name, char **args, t_ctx *ctx)
{
	int	exit_status;

	exit_status = 0;
	if (ft_strcmp(prog_name, "pwd") == 0)
		exit_status = pwd_btin();
	else if (ft_strcmp(prog_name, "cd") == 0)
		exit_status = chdir_btin(count_words(args),
				(const char **)args, ctx->envs);
	else if (ft_strcmp(prog_name, "export") == 0)
		exit_status = export_btin((char **)args, ctx->envs);
	else if (ft_strcmp(prog_name, "env") == 0)
		print_vars(ctx->envs, 1);
	else if (ft_strcmp(prog_name, "unset") == 0)
		exit_status = unset_btin(&ctx->envs, args);
	else if (ft_strcmp(prog_name, "echo") == 0)
		exit_status = echo_btin(args);
	else if (ft_strcmp(prog_name, "unset") == 0)
		exit_status = unset_btin(&ctx->envs, args);
	else if (ft_strcmp(prog_name, "exit") == 0)
		exit_status = exit_btin(count_words(args), args, ctx);
	return (exit_status);
}
