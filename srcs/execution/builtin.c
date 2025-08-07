/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 07:29:05 by dazzali           #+#    #+#             */
/*   Updated: 2025/08/11 07:47:52 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	_save_btin_fds(int *saved_stdin, int *saved_stdout);
static void	_exec_btin_err(int saved_stdin,
				int saved_stdout,
				t_ctx *ctx,
				int status);

int	handle_builtin_node(t_ast_node *node, t_ctx *ctx)
{
	int		std_stoud[2];

	if (is_builtin(node->value))
	{
		if (_save_btin_fds(&std_stoud[0], &std_stoud[1]) == -1)
			return (-1);
		if (handle_heredocs(node, ctx) == -1)
			return (_exec_btin_err(std_stoud[0], std_stoud[1], ctx, 1), -1);
		if (handle_redirections(node) == -1)
			return (_exec_btin_err(std_stoud[0], std_stoud[1], ctx, 1), -1);
		ctx->exit_status = execute_btin(node->value, node->args, ctx);
		if (dup2(std_stoud[0], STDIN_FILENO) == -1
			|| dup2(std_stoud[1], STDOUT_FILENO) == -1)
		{
			print_shell_error(strerror(errno));
			ctx->exit_status = 1;
		}
		_exec_btin_err(std_stoud[0], std_stoud[1], NULL, 0);
	}
	return (0);
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

static void	_exec_btin_err(int saved_stdin,
					int saved_stdout,
					t_ctx *ctx,
					int status)
{
	close(saved_stdin);
	close(saved_stdout);
	if (ctx)
		ctx->exit_status = status;
}
