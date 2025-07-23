/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 parse_user_line.c									:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/07/25 10:18:51 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/07/31 09:27:07 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "ast.h"

static int	_parse_error(t_parser *parser, char *line, char *message);
static void	process_new_line(char *line, t_ctx *ctx);

int	read_user_line(t_ctx *ctx)
{
	char				*line;

	while (1)
	{
		line = readline("minishell> ");
		if (line)
			process_new_line(line, ctx);
		else
			return (printf("exit\n"));
	}
	return (0);
}

static void	process_new_line(char *line, t_ctx *ctx)
{
	static t_parser		parser = {0};
	t_ast_node			*ast_root;
	char				*tmp;

	add_to_history_struct(line, ctx->history);
	tmp = ft_strtrim(line, " \t\r\n");
	free(line);
	line = tmp;
	if (line[0] == '\0')
	{
		free(line);
		return ;
	}
	ast_root = parse_new_line(line, &parser, ctx);
	if (!ast_root)
		return ;
	ctx->ast = ast_root;
	cleanup_tokenizer(&parser);
	debug_ast(ast_root);
	traverse_ast(ast_root, execute, ctx);
	free_ast_node(ast_root);
	free(line);
}

t_ast_node	*parse_new_line(char *line, t_parser *parser, t_ctx *ctx)
{
	t_ast_node	*ast_root;

	reset_tokenizer(parser, line);
	ctx->parser = parser;
	if (parse_line(line, ctx) == -1)
	{
		log_error("Failed to parse line\n");
		return (NULL);
	}
	ast_root = build_ast(ctx);
	if (!ast_root)
	{
		free(line);
		log_error("Failed to build ast\n");
	}
	return (ast_root);
}

int	parse_line(char *line, t_ctx *ctx)
{
	reset_tokenizer(ctx->parser, line);
	if (tokenize_line(ctx->parser, line) == -1)
		return (_parse_error(ctx->parser, line, "Failed to tokenize line\n"));
	if (expand_tokens(ctx) == -1)
		return (_parse_error(ctx->parser, line, "Failed to expand tokens\n"));
	if (remove_quotes(ctx) == -1)
		return (_parse_error(ctx->parser, line, "Failed to remove tokens\n"));
	if (recognize_tokens(ctx) == -1)
		return (_parse_error(ctx->parser,
				line, "Failed to recognize tokens\n"));
	return (0);
}

static int	_parse_error(t_parser *parser, char *line, char *message)
{
	if (message)
		log_error(message);
	cleanup_tokenizer(parser);
	free(line);
	return (-1);
}
