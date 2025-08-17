/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 execute_command.c									:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/07/26 08:36:37 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/07/26 08:38:50 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "execute.h"

static void	_execute_external_command(char *prog_name, char **args, t_ctx *ctx);

int	assign_status_to_ctx(int status, t_ast_node *node, t_ctx *ctx)
{
	signal(SIGINT, sig_handler_sigint);
	signal(SIGQUIT, SIG_IGN);
	if (node->input_fd != STDIN_FILENO)
		close(node->input_fd);
	if (WIFEXITED(status))
		ctx->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		ctx->exit_status = 128 + WTERMSIG(status);
	if (ctx->exit_status > 127)
		return (-1);
	return (0);
}

/** @brief Fork and execute the program specified in the node
 * */
int	execute_single_command(t_ast_node *node, t_ctx *ctx, char *prog_name)
{
	char	**args;
	int		pid;
	int		status;

	if (handle_heredocs(node, ctx) == -1)
		return (-1);
	args = build_args(node);
	if (!args)
		return (print_shell_error_ret_int(MALLOC_ERROR_MSG, -1));
	signal(SIGINT, sig_handler_sigint_in_process);
	signal(SIGQUIT, sigquit_handler_in_process);
	pid = fork();
	if (pid < 0)
		return (free(args), print_shell_error_ret_int("Fork error", -1));
	if (pid == 0)
	{
		if (handle_redirections(node) == -1)
			exit(1);
		execute_child_proc(prog_name, args, ctx);
	}
	waitpid(pid, &status, 0);
	if (assign_status_to_ctx(status, node, ctx) == -1)
		return (-1);
	free(args);
	return (0);
}

/**
 * _execute_child_proc - Execute a program in child process (never returns)
 * @prog_name: Program name to execute (not freed, caller owns)
 * @args: Argument array for execve (not freed, caller owns)
 * @ctx: Shell context containing environment variables (not freed)
 * 
 * This function:
 * 1. Converts environment to string array (allocates)
 * 2. Resolves executable path (may allocate)
 * 3. Calls execve() - on success, process is replaced
 * 4. On execve failure: cleans up local allocations and exits
 * 
 * Exit codes:
 * - errno-based code on execve/allocation failure
 * - 127 if command path cannot be resolved
*/
void	execute_child_proc(char *prog_name, char **args, t_ctx *ctx)
{
	int		exit_status;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	exit_status = 0;
	if (is_builtin(prog_name))
	{
		exit_status = execute_btin(prog_name, (args + 1), ctx);
		free(args);
		exit(exit_status);
	}
	_execute_external_command(prog_name, args, ctx);
}

static void	_execute_external_command(char *prog_name, char **args, t_ctx *ctx)
{
	char	**envs;
	char	*exec_path;

	envs = envs_to_strarr(ctx->envs);
	if (!envs)
	{
		print_shell_error(MALLOC_ERROR_MSG);
		free(args);
		exit(errno_to_shell_exit(errno));
	}
	exec_path = resolve_exec_path(prog_name, ctx);
	if (!exec_path)
	{
		ft_fprintf(2, "minishell: %s: command not found\n", prog_name);
		free_str_array(envs);
		free(args);
		exit(127);
	}
	execve(exec_path, args, envs);
	free_str_array(envs);
	if (exec_path != prog_name)
		free(exec_path);
	print_exec_err(errno, prog_name);
	exit(errno_to_shell_exit(errno));
}

/*
 * resolve_exec_path - Resolve the full path for a program
 * @prog_name: Program name to resolve (not freed, caller owns)
 * @ctx: Shell context containing environment variables (not freed)
 * 
 * Returns: 
 *	 - prog_name itself if it starts with "./"
 *	 - Newly allocated path string (caller must free) if PATH lookup succeeds
 *	 - Newly allocated copy of prog_name if no PATH variable exists
 *	 - NULL on allocation failure
 * 
 * Note: Caller must free returned value only if it differs from prog_name
 */
char	**build_args(t_ast_node *node)
{
	char	**args;
	size_t	len;	
	size_t	j;

	len = count_words(node->args);
	args = ft_calloc(len + 1 + 1, sizeof(char *));
	if (!args)
		return (print_shell_error_ret_null(MALLOC_ERROR_MSG));
	args[0] = node->value;
	j = 0;
	if (len == 0)
		return (args);
	while (node->args[j])
	{
		args[j + 1] = node->args[j];
		j++;
	}
	return (args);
}
