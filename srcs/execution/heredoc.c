/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 heredoc.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/08/07 12:22:10 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/08/07 13:16:53 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "execute.h"
#include "expander.h"

static int	_handle_child_heredoc(int fds_p[2], t_redir *content, t_ctx *ctx);
static int	handle_heredoc(t_ast_node *node, t_redir *content, t_ctx *ctx);
static int	_handle_parent_heredoc_signals(
				t_ast_node *node,
				t_ctx *ctx,
				int status,
				int fds_p[2]);

int	handle_pipes_heredocs(t_list *node, t_ctx *ctx)
{
	t_list		*head;
	t_ast_node	*tmp;

	head = node;
	while (node)
	{
		if (handle_heredocs(((t_ast_node *) node->content), ctx) == -1)
		{
			while (head)
			{
				tmp = head->content;
				if (head->next)
				{
					if (tmp->input_fd != STDIN_FILENO)
						close(tmp->input_fd);
				}
				head = head->next;
			}
			return (-1);
		}
		node = node->next;
	}
	return (0);
}

int	handle_heredocs(t_ast_node *node, t_ctx *ctx)
{
	t_list	*redirs_list;
	t_redir	*content;

	redirs_list = node->redirs;
	while (redirs_list)
	{
		content = redirs_list->content;
		if (content->type == TOK_REDIR_HEREDOC)
		{
			if (node->input_fd != STDIN_FILENO)
				close(node->input_fd);
			if (handle_heredoc(node, content, ctx) == -1)
				return (-1);
		}
		redirs_list = redirs_list->next;
	}
	return (0);
}

static int	handle_heredoc(t_ast_node *node, t_redir *content, t_ctx *ctx)
{
	int	fds_p[2];
	int	pid;
	int	status;

	if (!content)
		return (0);
	if (pipe(fds_p) == -1)
		return (perror("pipe: "), -1);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		_handle_child_heredoc(fds_p, content, ctx);
	close(fds_p[1]);
	if (waitpid(pid, &status, 0) == -1)
		return (print_shell_error_ret_int("Error in waitpid", -1));
	signal(SIGINT, sig_handler_sigint);
	if (WIFEXITED(status) && WEXITSTATUS(status) > 128)
	{
		if (_handle_parent_heredoc_signals(node, ctx, status, fds_p) == -1)
			return (-1);
	}
	node->input_fd = fds_p[0];
	return (0);
}

static int	_handle_parent_heredoc_signals(t_ast_node *node,
										t_ctx *ctx, int status,
										int fds_p[2])
{
	ctx->exit_status = WEXITSTATUS(status);
	close(fds_p[0]);
	if (WEXITSTATUS(status) == 130)
		return (-1);
	if (node->input_fd != STDIN_FILENO)
		return (-1);
	return (0);
}

static int	_handle_child_heredoc(int fds_p[2], t_redir *content, t_ctx *ctx)
{
	char	*res;

	signal(SIGINT, sig_handler_sigint_in_heredoc);
	close(fds_p[0]);
	while (1)
	{
		res = readline("> ");
		if (!res || ft_strcmp(res, content->target) == 0)
		{
			free(res);
			break ;
		}
		res = line_expansion(res, ctx);
		if (!res)
		{
			print_shell_error("Error in expander");
			break ;
		}
		ft_putstr_fd(res, fds_p[1]);
		ft_putstr_fd("\n", fds_p[1]);
		free(res);
	}
	close(fds_p[1]);
	exit(0);
}
