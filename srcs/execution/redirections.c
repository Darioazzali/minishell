/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 18:17:17 by dazzali           #+#    #+#             */
/*   Updated: 2025/07/31 07:50:11 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	_traverse_redir(t_list *redirs,
				t_redir **in_red, t_redir **out_red);
static int	_redirect(t_redir *in_red, t_redir *out_red);

int	_manage_redir(t_ast_node *node)
{
	t_redir	*in_red;
	t_redir	*out_red;
	t_list	*redirs;

	in_red = NULL;
	out_red = NULL;
	redirs = node->redirs;
	if (redirs)
		_traverse_redir(redirs, &in_red, &out_red);
	_redirect(in_red, out_red);
	return (0);
}

static void	_traverse_redir(t_list *redirs, t_redir **in_red, t_redir **out_red)
{
	t_redir	*content;

	while (redirs)
	{
		content = redirs->content;
		if (content->type == TOK_REDIR_IN)
			(*in_red) = content;
		else if (content->type == TOK_REDIR_OUT)
			(*out_red) = content;
		else if (content->type == TOK_REDIR_APPEND)
			(*out_red) = content;
		redirs = redirs->next;
	}
}

static int	_redirect(t_redir *in_red, t_redir *out_red)
{
	int	fd;

	if (in_red)
	{
		fd = open(in_red->target, O_RDONLY);
		if (fd == -1)
			return (print_shell_error_ret_int(strerror(errno), -1));
		if (dup2(fd, STDIN_FILENO) == -1)
			return (print_shell_error_ret_int(strerror(errno), -1));
		close(fd);
	}
	if (out_red)
	{
		if (out_red->type == TOK_REDIR_OUT)
			fd = open(out_red->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			fd = open(out_red->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			return (print_shell_error_ret_int(strerror(errno), -1));
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (print_shell_error_ret_int(strerror(errno), -1));
		close(fd);
	}
	return (0);
}

int	manage_fds(t_ast_node *node, int *open_fds, int opened_fds)
{
	int		i;

	if (dup2(node->input_fd, STDIN_FILENO) == -1)
		return (print_shell_error_ret_int(strerror(errno), -1));
	if (dup2(node->output_fd, STDOUT_FILENO) == -1)
	{
		close(node->input_fd);
		return (print_shell_error_ret_int(strerror(errno), -1));
	}
	i = 0;
	if (_manage_redir(node) == -1)
		return (-1);
	while (i < opened_fds)
	{
		if (open_fds[i] != node->input_fd && open_fds[i] != node->output_fd)
			close(open_fds[i]);
		i++;
	}
	return (0);
}
