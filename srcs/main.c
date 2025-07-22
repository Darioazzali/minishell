/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 prompt.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/06/12 11:37:16 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/06/12 11:40:58 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

static int	init_program(t_ctx **ctx, char **env);
static int	read_user_line(t_ctx *ctx);
static int	_parse_error(t_parser *parser, char *line, char *message);
static int	parse_line(char *line, t_ctx *ctx);

int	main(int argc, char **argv, char **env)
{
	t_ctx	*ctx;

	(void) argc;
	(void) argv;
	ctx = NULL;
	if (!init_program(&ctx, env))
		return (1);
	read_user_line(ctx);
	save_to_history_file(ctx->history);
	rl_clear_history();
	free_ctx(ctx);
	return (0);
}

static int	init_program(t_ctx **ctx, char **env)
{
	t_envs	*envs;

	*ctx = init_ctx();
	if (!*ctx)
		return (0);
	(*ctx)->history = init_history();
	if (!(*ctx)->history)
	{
		perror("Error: Couldn't initialize history\n");
		return (0);
	}
	envs = parse_envs(env);
	if (!envs)
	{
		free_ctx(*ctx);
		return (0);
	}
	(*ctx)->envs = envs;
	if (!(*ctx)->envs)
	{
		free_ctx(*ctx);
		return (0);
	}
	return (1);
}

static int	read_user_line(t_ctx *ctx)
{
	char				*line;
	t_ast_node			*ast_root;
	static t_parser		parser = {0};

	while (1)
	{
		line = readline("> ");
		if (line)
		{
			add_to_history_struct(line, ctx->history);
			reset_tokenizer(&parser, line);
			ctx->parser = &parser;
			if (parse_line(line, ctx) == -1)
				continue ;
			ast_root = build_ast(ctx);
			if (!ast_root)
			{
				log_error("AST construction failed\n");
				continue ;
			}
			log_debug("AST ready for execution\n");
			free_ast_node(ast_root);
			cleanup_tokenizer(&parser);
			free(line);
		}
		else
			return (printf("exit\n"));
	}
	return (0);
}

static int	parse_line(char *line, t_ctx *ctx)
{
	static t_parser		parser = {0};

	reset_tokenizer(&parser, line);
	ctx->parser = &parser;
	if (tokenize_line(&parser, line) == -1)
		return (_parse_error(&parser, line, "Failed to tokenize line\n"));
	if (expand_tokens(ctx) == -1)
		return (_parse_error(&parser, line, "Failed to expand tokens\n"));
	if (remove_quotes(ctx) == -1)
		return (_parse_error(&parser, line, "Failed to remove tokens\n"));
	if (recognize_tokens(ctx) == -1)
		return (_parse_error(&parser, line, "Failed to recognize tokens\n"));
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
