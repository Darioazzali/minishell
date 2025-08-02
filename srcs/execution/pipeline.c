/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 pipeline.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/07/29 08:17:49 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/07/29 08:37:58 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "execute.h"

int			fork_and_exec(t_ast_node *node,
				t_ctx *ctx, int *open_fds, int opened_fds);
static int	open_pipes(t_list *node, int *open_fds);
static int	*execute_pipeline(t_list *node, t_ctx *ctx,
				int *open_fds, int opened_fds);
static int	clean_pipelines_fds(t_list *node, int *open_fds, int idx);

void	handle_pipeline(t_list *node, t_ctx *ctx)
{
	pid_t		*pids;
	size_t		count;
	int			*open_fds;
	int			opened_fds;
	size_t		i;

	count = ft_lstsize(node);
	open_fds = ft_calloc(count * 2, sizeof(int));
	if (!open_fds)
		return (print_shell_error(MALLOC_ERROR_MSG));
	opened_fds = open_pipes(node, open_fds);
	if (opened_fds == -1)
		return ;
	pids = execute_pipeline(node, ctx, open_fds, opened_fds);
	if (!pids)
	{
		clean_pipelines_fds(node, open_fds, opened_fds);
		return ;
	}
	i = 0;
	while (i < count)
		waitpid(pids[i++], NULL, 0);
	free(open_fds);
	free(pids);
}

/** Execute the pipeline
 * Execute the pipeline subtree.
 *
 * @param node The root node of the pipeline
 * @param ctx The context
 * @param open_fds The array of the opened fds of the pipeline
 * @param opened_fds The number of opened fds
 *
 * @return The array of the child pids or NULL in case of error
 *
 * @note The function can fail on:
 * 1. Fail to allocate memory for the pids
 * 2. Fail to fork
 * 3. Fork and exec fails to build the argument command
 *
 * */
static int	*execute_pipeline(t_list *node, t_ctx *ctx,
				int *open_fds, int opened_fds)
{
	pid_t		*pids;
	int			idx;

	pids = ft_calloc(ft_lstsize(node), sizeof(pid_t));
	if (!pids)
		return (print_shell_error_ret_null(MALLOC_ERROR_MSG));
	idx = 0;
	while (node)
	{
		pids[idx] = fork_and_exec((t_ast_node *)node->content,
				ctx, open_fds, opened_fds);
		if (pids[idx++] == -1)
		{
			while (--idx >= 0)
				waitpid(pids[idx], NULL, 0);
			free(pids);
			return (print_shell_error_ret_null(strerror(errno)));
		}
		if (((t_ast_node *)(node->content))->input_fd != STDIN_FILENO)
			close(((t_ast_node *)(node->content))->input_fd);
		if (((t_ast_node *)(node->content))->output_fd != STDOUT_FILENO)
			close(((t_ast_node *)(node->content))->output_fd);
		node = node->next;
	}
	return (pids);
}

/** @brief Fork the process and execute it
 * Fork the process in the node and launch execution.
 *
 * @return The pid or -1 on error
 * @note The function can fail on:
 * 1. Fork
 * 2. Error to allocate the args
 * */
int	fork_and_exec(t_ast_node *node,
			t_ctx *ctx, int *open_fds, int opened_fds)
{
	char	**args;
	pid_t	pid;

	args = build_args(node);
	if (!args)
		return (print_shell_error_ret_int(MALLOC_ERROR_MSG, -1));
	pid = fork();
	if (pid == -1)
	{
		free(args);
		return (print_shell_error_ret_int(strerror(errno), -1));
	}
	if (pid == 0)
	{
		if (manage_fds(node, open_fds, opened_fds) == -1)
		{
			free(args);
			return (-1);
		}
		execute_child_proc(node->value, args, ctx);
	}
	return (pid);
}

/** @brief Open all the pipes of the pipeline
 *
 *	Open all the pipes needed by the pipeline subtree and store
 *	the results in the array of opened fds.
 *
 *	@param node The pipeline subtree
 *	@param open_fds The array of opened fds
 *
 * @note The idx parameter is the number of opened pipes
 *       while the number of open_fds is 2 * idx
 *	@return The length of the array
 * */
static int	open_pipes(t_list *node, int *open_fds)
{
	int				idx;
	t_list			*current;
	t_list			*last;
	t_ast_node		*node_content;
	int				fds[2];

	idx = 0;
	current = node;
	last = ft_lstlast(node);
	while (current && current != last)
	{
		if (pipe(fds) == -1)
		{
			print_shell_error(strerror(errno));
			return (clean_pipelines_fds(node, open_fds, idx * 2));
		}
		node_content = (t_ast_node *)current->content;
		node_content->output_fd = fds[1];
		((t_ast_node *)(current->next->content))->input_fd = fds[0];
		open_fds[idx * 2] = fds[0];
		open_fds[(2 * idx) + 1] = fds[1];
		idx++;
		current = current->next;
	}
	return (idx * 2);
}

/** @brief Clean the opened pipes and return an error
 * Close the all file descriptors built by the pipeline
 *  reset the node states of all the pipe subtree,
 *  free the open_fds array and return -1.
 *  with errno indicating the
 * error state.
 *
 * @param node The pipeline subtree
 * @param open_fds The array of opened fds
 * @param idx The number of openeded fds, aka the length of the array.
 *
 * @note The function saves the errno value before close in order
 * to not clutter the information of the pipe error to the user.
 * */
static int	clean_pipelines_fds(t_list *node, int *open_fds, int opened_fds)
{
	t_ast_node	*current;

	while (opened_fds)
		close(open_fds[--opened_fds]);
	while (node)
	{
		current = (t_ast_node *)node->content;
		current->input_fd = STDIN_FILENO;
		current->output_fd = STDOUT_FILENO;
		node = node->next;
	}
	free(open_fds);
	return (-1);
}
