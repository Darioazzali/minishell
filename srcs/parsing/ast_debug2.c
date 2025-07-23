/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ast_debug2.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/07/23 18:52:25 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/07/29 10:19:42 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "ast_debug.h"

static void	append_newline_with_indent(char *line, int depth, int extra_indent);

void	debug_ast_command_args(char *line, t_ast_node *node)
{
	int	i;

	ft_strlcat(line, " [", BUF_SIZE);
	i = 0;
	while (node->args[i])
	{
		ft_strlcat(line, "\"", BUF_SIZE);
		ft_strlcat(line, node->args[i], BUF_SIZE);
		ft_strlcat(line, "\"", BUF_SIZE);
		if (node->args[i + 1])
			ft_strlcat(line, ", ", BUF_SIZE);
		i++;
	}
	ft_strlcat(line, "]", BUF_SIZE);
}

void	debug_ast_command_redirs(char *line, t_ast_node *node, int depth)
{
	t_list	*tmp;
	t_redir	*content;

	tmp = node->redirs;
	if (!tmp)
		return ;
	append_newline_with_indent(line, depth, 0);
	ft_strlcat(line, " REDIRECTS: [", BUF_SIZE);
	while (tmp)
	{
		content = (t_redir *)tmp->content;
		append_newline_with_indent(line, depth, 1);
		ft_strlcat(line, "TYPE: ", BUF_SIZE);
		ft_strlcat(line, get_token_type_str(content->type), BUF_SIZE);
		ft_strlcat(line, ", ", BUF_SIZE);
		ft_strlcat(line, "Target: ", BUF_SIZE);
		ft_strlcat(line, content->target, BUF_SIZE);
		ft_strlcat(line, "\n", BUF_SIZE);
		tmp = tmp->next;
	}
	ft_strlcat(line, "]", BUF_SIZE);
}

void	debug_ast_commands_fds(char *line, t_ast_node *node, int depth)
{
	char	*input_fd;
	char	*output_fd;

	append_newline_with_indent(line, depth, 1);
	ft_strlcat(line, " FDS: [", BUF_SIZE);
	input_fd = ft_itoa(node->input_fd);
	output_fd = ft_itoa(node->output_fd);
	ft_strlcat(line, "INPUT_FD: ", BUF_SIZE);
	ft_strlcat(line, input_fd, BUF_SIZE);
	ft_strlcat(line, ", ", BUF_SIZE);
	ft_strlcat(line, "OUTPUT_FD: ", BUF_SIZE);
	ft_strlcat(line, output_fd, BUF_SIZE);
	ft_strlcat(line, "]", BUF_SIZE);
}

void	append_node_type(char *line, t_ast_node *node)
{
	if (node->type == AST_LOGICAL)
		ft_strlcat(line, "AST_LOGICAL (\"", BUF_SIZE);
	else if (node->type == AST_PIPELINE)
		ft_strlcat(line, "AST_PIPELINE (\"", BUF_SIZE);
	else if (node->type == AST_COMMAND)
		ft_strlcat(line, "AST_COMMAND (\"", BUF_SIZE);
	ft_strlcat(line, node->value, BUF_SIZE);
	ft_strlcat(line, "\")", BUF_SIZE);
}

static void	append_newline_with_indent(char *line, int depth, int extra_indent)
{
	int	total_spaces;
	int	i;

	total_spaces = depth * 4 + extra_indent;
	ft_strlcat(line, "\n", BUF_SIZE);
	i = 0;
	while (i < total_spaces)
	{
		ft_strlcat(line, " ", BUF_SIZE);
		i++;
	}
}
