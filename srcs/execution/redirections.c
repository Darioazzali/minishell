/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 redirections.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/07/30 18:17:17 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/08/03 08:44:21 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "execute.h"
#include "ast_debug.h"

static int	_traverse_redir(t_ast_node *node, int *fds);
static int	_redirect(t_ast_node *node);
static int	open_and_assign_redirect(
				t_ast_node *node,
				t_redir *content,
				int *fds,
				size_t *i);

/**	@brief  Handle redirections of a node.
 *
 * 			If a node has redirections, open the files and redirect the	
 * 			stdin and stdout to the files.
 *
 * @return	0 if no error
 *
 * 	@note	Can fail if:
 * 			malloc fails to allocate the open_fds
 * 			There is an error during file opening
 * 			There is an error while duplicating the fds
 * 					
 * */
int	handle_redirections(t_ast_node *node)
{
	t_list	*redirs;
	int		*fds;

	redirs = node->redirs;
	if (redirs)
	{
		fds = ft_calloc(ft_lstsize(redirs), sizeof(int));
		if (!fds)
			return (print_shell_error_ret_int(MALLOC_ERROR_MSG, -1));
		if (_traverse_redir(node, fds) == -1)
		{
			free(fds);
			return (-1);
		}
		node->open_fds = fds;
		if (_redirect(node) == -1)
			return (-1);
	}
	return (0);
}

/** @brief Traverse the redir list and open the files.
 *
 * The bash behavior is to open the files in the order they are in the list
 * and as soon as encounter an error during file opening, stop the redirection
 * and return error that has encountered.
 * */
static int	_traverse_redir(t_ast_node *node, int *fds)
{
	t_redir		*content;
	t_list		*redirs;
	size_t		i;

	redirs = node->redirs;
	i = 0;
	while (redirs)
	{
		content = redirs->content;
		if (content->type != TOK_REDIR_HEREDOC)
		{
			if (open_and_assign_redirect(node, content, fds, &i) == -1)
			{
				while (i)
					close(fds[--i]);
				return (-1);
			}
			i++;
		}
		redirs = redirs->next;
	}
	return (0);
}

/** @brief	Redirect the file descriptors to the opened fds 
 * 			stored in the node input/output_fd
 *
 * 			
 **/
static int	_redirect(t_ast_node *node)
{
	if (node->input_fd != STDIN_FILENO)
	{
		if (dup2(node->input_fd, STDIN_FILENO) == -1)
		{
			return (print_shell_error_ret_int(strerror(errno), -1));
		}
		close(node->input_fd);
	}
	if (node->output_fd != STDOUT_FILENO)
	{
		if (dup2(node->output_fd, STDOUT_FILENO) == -1)
		{
			return (print_shell_error_ret_int(strerror(errno), -1));
		}
		close(node->output_fd);
	}
	return (0);
}

/** @brief Manage the files descriptors during the pipeline execution
 *
 *
 * The file descriptors are managed as follows:
 * if a pipeline is active the fds stored in input_fd and output_fd
 * are different from stdin and stdout, so the fds relative to the 
 * pipeline are duplicated to the new stdin and stdout.
 *
 * 
 * @note This function is called by the child process.
 * */
int	manage_pipeline_fds(t_ast_node *node, int *open_fds, int opened_fds)
{
	int		i;

	if (node->input_fd != STDIN_FILENO)
	{
		if (dup2(node->input_fd, STDIN_FILENO) == -1)
			return (print_shell_error_ret_int(strerror(errno), -1));
		close(node->input_fd);
		node->input_fd = STDIN_FILENO;
	}
	if (node->output_fd != STDOUT_FILENO)
	{
		if (dup2(node->output_fd, STDOUT_FILENO) == -1)
			return (print_shell_error_ret_int(strerror(errno), -1));
		close(node->output_fd);
		node->output_fd = STDOUT_FILENO;
	}
	debug_ast_node(node);
	if (handle_redirections(node) == -1)
		return (-1);
	i = -1;
	while (++i < opened_fds)
		if (open_fds[i] != node->input_fd && open_fds[i] != node->output_fd)
			close(open_fds[i]);
	return (0);
}

/**	@brief Open the file and assign it to the node
 *	
 *	Open the file descriptors associated to the redirections
 *	of the node and assign them to the node input_fd and output_fd.
 *
 *	@return 0 if no error
 *
 *	@note	Can fail if there is an error during file opening
 *	*/
static int	open_and_assign_redirect(t_ast_node *node,
								t_redir *content, int *fds, size_t *i)
{
	int	fd;

	if (content->type == TOK_REDIR_IN)
	{
		fd = open(content->target, O_RDONLY);
		if (fd == -1)
			return (print_shell_error_ret_int(strerror(errno), -1));
		node->input_fd = fd;
	}
	else if (content->type == TOK_REDIR_OUT)
	{
		fd = open(content->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (print_shell_error_ret_int(strerror(errno), -1));
		node->output_fd = fd;
	}
	else
	{
		fd = open(content->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			return (print_shell_error_ret_int(strerror(errno), -1));
		node->output_fd = fd;
	}
	fds[*i] = fd;
	return (0);
}
