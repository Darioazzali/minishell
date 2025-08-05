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
static int	_save_btin_fds(int *saved_stdin, int *saved_stdout);

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
	int		std_stoud[2];

	if (is_builtin(node->value))
	{
		if (_save_btin_fds(&std_stoud[0], &std_stoud[1]) == -1)
			return ;
		if (handle_redirections(node) == -1)
		{
			close(std_stoud[0]);
			close(std_stoud[1]);
			ctx->exit_status = 1;
			return ;
		}
		ctx->exit_status = execute_btin(node->value, node->args, ctx);
		if (dup2(std_stoud[0], STDIN_FILENO) == -1
			|| dup2(std_stoud[1], STDOUT_FILENO) == -1)
		{
			print_shell_error(strerror(errno));
			ctx->exit_status = 1;
		}
		close(std_stoud[0]);
		close(std_stoud[1]);
	}
	else
		execute_single_command(node, ctx, node->value);
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
	if (ft_strcmp(command, "env") == 0)
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
	else if (ft_strcmp(prog_name, "exit") == 0)
		exit_status = exit_btin(count_words(args), args, ctx);
	return (exit_status);
}

/** @brief Save stdin and stdout for the builtin programs.
 *	
 *	When a builtin program is executed as a single command
 *	the process is not forked, so we need to save stdin and stdout
 *	because after the redirections are applied the execution
 *	continue in the parent process so we need to restore them 
 *	as soon as the builtin is done.
 *	
 *	@param saved_stdin - Pointer to save the old stdin
 *	@param saved_stdout - Pointer to save the old stdout
 *
 * @return 0 if success
 *
 * @note If the duplication fails, the function returns -1
 * */
static int	_save_btin_fds(int *saved_stdin, int *saved_stdout)
{
	int		dup2_error;

	*saved_stdin = dup(STDIN_FILENO);
	if (*saved_stdin == -1)
	{
		dup2_error = errno;
		log_error("Failed to duplicate stdin\n");
		print_shell_error(strerror(dup2_error));
		return (-1);
	}
	*saved_stdout = dup(STDOUT_FILENO);
	if (*saved_stdout == -1)
	{
		dup2_error = errno;
		log_error("Failed to duplicate stdout\n");
		close(*saved_stdin);
		print_shell_error(strerror(dup2_error));
		return (-1);
	}
	return (0);
}
