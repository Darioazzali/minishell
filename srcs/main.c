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
#include "log.h"
#include "parser.h"

static int	init_program(t_ctx **ctx, char **env);
static int	read_user_line(t_ctx *ctx);

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
	char		*line;
	t_ast_node	*ast_root;

	while (1)
	{
		line = readline("> ");
		if (line)
		{
			add_to_history_struct(line, ctx->history);
			if (tokenize_line(ctx, line) == -1)
			{
				print_shell_error("error while parsing line");
				continue ;
			}
			if (expand_tokens(ctx) == -1)
				continue ;
			remove_quotes(ctx);
			recognize_tokens(ctx);
			ast_root = build_ast(ctx);
			if (!ast_root)
			{
				log_error(ctx->logger, "AST construction failed");
				continue ;
			}
			log_debug(ctx->logger, "AST ready for execution");
			free_ast_node(ast_root);
			free(line);
		}
		else
			return (printf("exit\n"));
	}
	return (0);
}
