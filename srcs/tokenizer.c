/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 parser.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/06/12 15:14:32 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/06/12 17:22:24 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "parser.h"

static char		*handle_normal_mode(t_ctx *ctx, char *line);
static char		*handle_single_quotes(t_ctx *ctx, char *line);
static char		*handle_double_quotes(t_ctx *ctx, char *line);
static int		add_token(t_ctx *ctx, char *start, char *end);

int	tokenize_line(t_ctx *ctx, char *line)
{
	t_parser	*parser;

	ctx->parser = malloc(sizeof(t_parser));
	if (!ctx->parser)
		return (-1);
	parser = ctx->parser;
	parser->ptr = line;
	parser->mode = LEXI_NORMAL;
	parser->tokens = NULL;
	while (*parser->ptr)
	{
		if (ctx->parser->mode == LEXI_NORMAL)
			parser->ptr = handle_normal_mode(ctx, parser->ptr);
		else if (parser->mode == LEXI_D_QUOTE)
			parser->ptr = handle_double_quotes(ctx, parser->ptr);
		else if (ctx->parser->mode == LEXI_S_QUOTE)
			parser->ptr = handle_single_quotes(ctx, parser->ptr);
	}
	if (ctx->parser->mode != LEXI_NORMAL)
	{
		log_error(ctx->logger, "Error, unterminated quote");
		return (-1);
	}
	return (0);
}

static	char	*handle_double_quotes(t_ctx *ctx, char *line)
{
	char	*start;

	start = line;
	line++;
	while (*line)
	{
		if (*line == '"')
		{
			log_debug(ctx->logger, "Exiting double quote mode");
			ctx->parser->mode = LEXI_NORMAL;
			break ;
		}
		line++;
	}
	add_token(ctx, start, line + 1);
	line++;
	log_debug(ctx->logger, "Exiting normal mode");
	return (line);
}

static	char	*handle_normal_mode(t_ctx *ctx, char *line)
{
	char	*start;

	start = line;
	while (*line && *line == ' ')
		line++;
	start = line;
	while (*line && *line != ' ')
	{
		if (*line == '\'')
		{
			ctx->parser->mode = LEXI_S_QUOTE;
			return (line);
		}
		else if (*line == '"')
		{
			log_debug(ctx->logger, "Entering double quote mode");
			ctx->parser->mode = LEXI_D_QUOTE;
			return (line);
		}
		line++;
	}
	add_token(ctx, start, line);
	log_debug(ctx->logger, "Exiting normal mode");
	return (line);
}

static	char	*handle_single_quotes(t_ctx *ctx, char *line)
{
	char	*start;

	log_debug(ctx->logger, "Entering single quote mode");
	start = line;
	line++;
	while (*line)
	{
		if (*line == '\'')
		{
			add_token(ctx, start, line);
			ctx->parser->mode = LEXI_NORMAL;
			log_debug(ctx->logger, "Exiting single quote mode");
			line++;
			return (line);
		}
		line++;
	}
	return (line);
}

static int	add_token(t_ctx *ctx, char *start, char *end)
{
	t_list	*new;
	char	*new_str;

	log_debug(ctx->logger, "Adding token");
	new_str = ft_substr(start, 0, end - start + 1);
	log_debug(ctx->logger, new_str);
	if (!new_str)
		return (0);
	new = ft_lstnew(new_str);
	if (!new)
	{
		free(new_str);
		return (0);
	}
	ft_lstadd_back(&ctx->parser->tokens, new);
	return (1);
}
